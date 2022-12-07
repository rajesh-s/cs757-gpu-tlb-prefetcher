#include "src/arch/amdgpu/common/ldt.hh"

namespace gem5
{

namespace X86ISA
{

	LDT::LDT(const Params &p) {

		//TODO : Change numCU param name to what's used 
		for (int i = 0; i < p.port_cpu_side_ports_connection_count; ++i) {
			l1SideReqPort.push_back(new L1SideReqPort(csprintf("%s-req-port%d", name(), i), this, i));
			l1SideRspPort.push_back(new L1SideRspPort(csprintf("%s-resp-port%d", name(), i), this, i));
		}

	l2SidePort.push_back(new L2SidePort(csprint("s-port%d", name(), i),this);
    accessLatency = p.LDTAccessLatency;
	}

	LDT::~LDT() {
		for (int i = 0; i <p.port_cpu_side_ports_connection_count; ++i)
		{
			delete l1SideReqPort[i];
			l1SideReqPort.pop_back();
			delete l1SideRspPort[i];
			l1SideRspPort.pop_back();
		}
		L2SidePort* l2Port = l2SidePort.pop_back();
		delete l2Port;
	}

	LDT::lookup(Addr va) {
		PacketPtr ptr;
		LDTEntry *entry;
		if (LdtList[va] == std::end) {
		    // Perform Replacement
		} else {
			entry = LdtList[va];
			ptr = entry->ptr;
		}
		for (int i = 0; i < entry->bitmap.size(); ++i) {
			l1SideReqPort[i].sendFunctional(pkt);
		}
	}

	LDT::update(Addr va, Packet ptr, int cu_num) {
		if (LdtList[va] == std::end) {
			LDTEntry* entry = new LDTEntry(pkt);
			entry->bitmap.push_back(cu_num);
			LdtList[va] = entry;
		} else {
			LDTEntry* entry = LdtList[va];
			bool exists = false;
			for (int i = 0; i < entry->bitmap.size(); ++i) {
				if (entry->bitmap[i] == cu_num) {
					exists = true;
					break;
				}
				if (!exists) entry->bitmap.push_back(cu_num);
			}
		}
	}
}
