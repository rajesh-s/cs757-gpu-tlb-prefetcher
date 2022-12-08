#include "arch/amdgpu/common/ldt.hh"

namespace gem5
{

namespace X86ISA
{

	LDT::LDT(const Params &p) :
		ClockedObject(p) {

		//TODO : Change numCU param name to what's used 
		for (int i = 0; i < p.port_cpu_side_ports_connection_count; ++i) {
			l1SideReqPort.push_back(new L1SideReqPort(csprintf("%s-req-port%d", name(), i), this, i));
			l1SideRspPort.push_back(new L1SideRspPort(csprintf("%s-resp-port%d", name(), i), this, i));
		}

	l2SidePort = new L2SidePort(csprintf("%s-port", name()),this);
    lookupLatency = p.LDTLookupLatency;
    updateLatency = p.LDTUpdateLatency;
    size = p.LDTSize;
	}

	LDT::~LDT() {
		for (int i = 0; i < p.port_cpu_side_ports_connection_count; ++i)
		{
			delete l1SideReqPort[i];
			l1SideReqPort.pop_back();
			delete l1SideRspPort[i];
			l1SideRspPort.pop_back();
		}
		delete l2SidePort;
	}

	void LDT::lookup(Addr va) {
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
			if (LdtList.size() == this->size) {
				delete LdtList.front();
				LdtList.pop_front();
			}
			LdtList.push_back(new LDTEntry(pkt));
		}
	}

	void LDT::issueLookup(PacketPtr pkt) {
		LDTEvent *event = new LDTEvent(this, pkt->getAddr(), pkt, true, 0);
		schedule(event, curTick() + cyclesToTicks(Cycles(lookupLatency)));

		LDTAccessEvent[pkt->getAddr()] = event;
	}

	void LDT::issueUpdate(PacketPtr pkt, int index) {
		LDTEvent *event = new LDTEvent(this, pkt->getAddr(), pkt, false, index);
		schedule(event, curTick() + cyclesToTicks(Cycles(updateLatency)));
		LDTAccessEvent[pkt->getAddr()] = event;
	}

	void LDT::LDTEvent::process() {
		if (this->isLookup)
			this->ldt->lookup(this->addr);
		else
			this->ldt->update(this->addr, this->pkt, this->index);
	}
	
	bool LDT::L1SideReqPort::recvTimingResp(PacketPtr pkt) {
		this->ldt->issueUpdate(pkt, this->index);
	}

	bool LDT::L2SidePort::recvTimingResp(PacketPtr pkt) {
		this->ldt->issueLookup(pkt);
	}
}

}
