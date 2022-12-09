#include "arch/amdgpu/common/ldt.hh"

namespace gem5
{

namespace X86ISA
{

	LDT::LDT(const Params &p) :
		ClockedObject(p) {
		DPRINTF(GPUTLB, "Inside LDT()\n");

		for (int i = 0; i < p.LDTNumOutPorts; ++i) {
			l1SideReqPort.push_back(new L1SideReqPort(csprintf("%s-req-port%d", name(), i), this, i));
			l1SideRspPort.push_back(new L1SideRspPort(csprintf("%s-resp-port%d", name(), i), this, i));
		}

	l2SidePort = new L2SidePort(csprintf("%s-port", name()),this);
    lookupLatency = p.LDTLookupLatency;
    updateLatency = p.LDTUpdateLatency;
    LDTSize = p.LDTSize;
	}

	LDT::~LDT() {
		int size = l1SideReqPort.size();
		DPRINTF(GPUTLB, "Inside ~LDT()\n");
		for (int i = 0; i < size; ++i)
		{
			delete l1SideReqPort[i];
			l1SideReqPort.pop_back();
			delete l1SideRspPort[i];
			l1SideRspPort.pop_back();
		}
		delete l2SidePort;
	}

	void LDT::lookup(Addr va) {
		DPRINTF(GPUTLB, "Inside lookup\n");
		PacketPtr pkt;
		LDTEntry *entry;
		for (auto it = LdtList.begin(); it != LdtList.end(); ++it) {
			LDTEntry* entry = (*it);
			if (va == entry->pkt->getAddr()) {

				pkt = entry->pkt;
				LdtList.erase(it);
				LdtList.push_back(entry);
				for (int i = 0; i < entry->bitmap.size(); ++i) {
					l1SideReqPort[i]->sendFunctional(pkt);
				}
				break;
			}
		}
	}

	void LDT::update(Addr va, PacketPtr pkt, int cu_num) {
		DPRINTF(GPUTLB, "Inside update"\n");
		bool isExists = false;
		for (auto it = LdtList.begin(); it != LdtList.end(); ++it) {
			LDTEntry* entry = (*it);
			if (va == entry->pkt->getAddr()) {
				isExists = true;
				bool isExistsInBitmap = false;
				for (int i = 0; i < entry->bitmap.size(); ++i) {
					if (entry->bitmap[i] == cu_num) {
						isExistsInBitmap = true;
						break;
					}
				}
				if (!isExistsInBitmap) entry->bitmap.push_back(cu_num);
				break;
			}
		}
		if (isExists == false) {
			if (LdtList.size() == this->LDTSize) {
				delete LdtList.front();
				LdtList.pop_front();
			}
			LdtList.push_back(new LDTEntry(pkt));
		}
	}

	void LDT::issueLookup(PacketPtr pkt) {
		DPRINTF(GPUTLB, "Inside issueLookup\n");
		LDTEvent *event = new LDTEvent(this, pkt->getAddr(), pkt, true, 0);
		schedule(event, curTick() + cyclesToTicks(Cycles(lookupLatency)));

		LDTAccessEvent[pkt->getAddr()] = event;
	}

	void LDT::issueUpdate(PacketPtr pkt, int index) {
		DPRINTF(GPUTLB, "Inside issueUpdate\n");
		LDTEvent *event = new LDTEvent(this, pkt->getAddr(), pkt, false, index);
		schedule(event, curTick() + cyclesToTicks(Cycles(updateLatency)));
		LDTAccessEvent[pkt->getAddr()] = event;
	}

	void LDT::LDTEvent::process() {
		DPRINTF(GPUTLB, "Inside process\n");
		Addr virt_page_addr = roundDown(this->addr, X86ISA::PageBytes);
		if (this->isLookup) 
			this->ldt->lookup(virt_page_addr);
		else {
			this->ldt->update(virt_page_addr, this->pkt, this->index);
		}
	}
	
	bool LDT::L1SideReqPort::recvTimingResp(PacketPtr pkt) {
		DPRINTF(GPUTLB, "Inside L1SideReqPort::recvTimingResp\n");
		this->ldt->issueUpdate(pkt, this->index);
	}

	bool LDT::L2SidePort::recvTimingResp(PacketPtr pkt) {
		DPRINTF(GPUTLB, "Inside L2SideReqPort::recvTimingResp\n");
		this->ldt->issueLookup(pkt);
	}

        Port &
        LDT::getPort(const std::string &if_name, PortID idx)
        {
            if (if_name == "l1_side_port") {
              return *l1SideRspPort;
    	    } else if (if_name == "l2_side_port") {
    	      return *l2SidePort;
            } else {
                panic("TLBCoalescer::getPort: unknown port %s\n", if_name);
            }
        }
}

}