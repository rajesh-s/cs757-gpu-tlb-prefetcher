/*
 * Copyright (c) 2011-2015 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __LDT_HH__
#define __LDT_HH__

#include <fstream>
#include <list>
#include <queue>
#include <string>
#include <vector>

#include "arch/generic/tlb.hh"
#include "arch/x86/pagetable.hh"
#include "arch/x86/pagetable_walker.hh"
#include "arch/x86/regs/segment.hh"
#include "base/callback.hh"
#include "base/logging.hh"
#include "base/statistics.hh"
#include "base/stats/group.hh"
#include "gpu-compute/compute_unit.hh"
#include "mem/port.hh"
#include "mem/request.hh"
#include "params/LDT.hh"
#include "sim/clocked_object.hh"
#include "sim/sim_object.hh"

namespace gem5
{

class BaseTLB;
class Packet;
class ThreadContext;

namespace X86ISA
{

    class LDTEntry
    {
		public:
			int index;
			std::vector<int> bitmap;
			PacketPtr pkt;
			LDTEntry(PacketPtr _pkt) :
				pkt(_pkt) {}
    };


    class LDT : public ClockedObject
    {

      public:
		  std::list<LDTEntry*> LdtList; 
		  // Bounded list?
		  typedef LDTParams Params;
		  LDT(const Params &p);
		  ~LDT();
		  typedef enum BaseMMU::Mode Mode;

          void dumpAll();
          void lookup(Addr va);
	  void update(Addr va, PacketPtr pkt, int cu_num);
 	  void issueLookup(PacketPtr pkt);
 	  void issueUpdate(PacketPtr pkt, int index);
          int lookupLatency;
	  int updateLatency;
	  int LDTSize;

	  Port &getPort(const std::string &if_name,
			  PortID idx=InvalidPortID) override;


        // L1SideReqPort is the LDT Port facing L1-TLB
        class L1SideReqPort : public RequestPort 
		{

          public:
            L1SideReqPort(const std::string &_name, LDT * _ldt,
                        PortID _index)
                : RequestPort(_name, _ldt), ldt(_ldt), index(_index) { }

            std::deque<PacketPtr> retries;

          protected:
	    LDT* ldt;
            int index;

            virtual bool recvTimingResp(PacketPtr pkt);
            virtual Tick recvAtomic(PacketPtr pkt) { return 0; }
            virtual void recvFunctional(PacketPtr pkt) { }
            virtual void recvRangeChange() { }
            virtual void recvReqRetry() { }

		};
        class LDTEvent : public Event
        {
            private:
                PacketPtr pkt;
		Addr addr;
		LDT *ldt;
		bool isLookup;
		int index;

            public:
                LDTEvent(LDT *_ldt, Addr _addr, PacketPtr _pkt, bool _isLookup, int _index) :
			ldt(_ldt), addr(_addr), pkt(_pkt), isLookup(_isLookup), index(_index) {}
                void process();
        };

        class L1SideRspPort : public ResponsePort
        {
          public:
            L1SideRspPort(const std::string &_name, LDT * _ldt,
                        PortID _index)
                : ResponsePort(_name, _ldt), ldt(_ldt), index(_index) { }

          protected:
            LDT *ldt;
            int index;

            virtual bool recvTimingReq(PacketPtr pkt) { }
            virtual Tick recvAtomic(PacketPtr pkt) { return 0; }
            virtual void recvFunctional(PacketPtr pkt) { }
            virtual void recvRangeChange() { }
            virtual void recvReqRetry() { }
            virtual void recvRespRetry() { panic("recvRespRetry called"); }
            virtual AddrRangeList getAddrRanges() const { }
        };

        class L2SidePort : public RequestPort
        {
          public:
            L2SidePort(const std::string &_name, LDT * _ldt)
                : RequestPort(_name, _ldt), ldt(_ldt) { }

            std::deque<PacketPtr> retries;

          protected:
            LDT *ldt;

            virtual bool recvTimingResp(PacketPtr pkt);
            virtual Tick recvAtomic(PacketPtr pkt) { return 0; }
            virtual void recvFunctional(PacketPtr pkt) { }
            virtual void recvRangeChange() { }
            virtual void recvReqRetry() { }
        };

        
		// TLB ports on the L1 Side
        std::vector<L1SideReqPort*> l1SideReqPort;
        std::vector<L1SideRspPort*> l1SideRspPort;
        // TLB ports on the memory side
        L2SidePort *l2SidePort;
	std::unordered_map<Addr, LDTEvent*> LDTAccessEvent;

//        Port &getPort(const std::string &if_name,
//                      PortID idx=InvalidPortID) override;



      protected:
//        struct LDTStats : public statistics::Group
//        {
//            LDTStats(statistics::Group *parent);
//
//            // local_stats are as seen from the TLB
//            // without taking into account coalescing
//            statistics::Scalar numLDTAccesses;
//            statistics::Scalar numLDTHits;
//            statistics::Scalar numLDTMisses;
//            statistics::Formula localTLBMissRate;
//
//            // from the CU perspective (global)
//            statistics::Scalar accessCycles;
//            // from the CU perspective (global)
//            statistics::Scalar pageTableCycles;
//            statistics::Scalar numUniquePages;
//            // from the perspective of this TLB
//            statistics::Scalar localCycles;
//            // from the perspective of this TLB
//            statistics::Formula localLatency;
//            // I take the avg. per page and then
//            // the avg. over all pages.
//            statistics::Scalar avgReuseDistance;
//        } stats;
    };
}

} // namespace gem5

#endif // __GPU_TLB_HH__
