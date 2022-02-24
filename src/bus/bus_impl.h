#ifndef GBEMU_BUS_IMPL_H_
#define GBEMU_BUS_IMPL_H_

#include "bus/bus.h"
#include "graphics/ppu.h"
#include "interrupt/interrupt_controller.h"
#include "memory/mbc.h"
#include "memory/ram.h"
#include "types/types.h"

namespace gbemu {

class BusImpl : public Bus {
 public:
  BusImpl(Mbc* mbc_, Ram* wram_, Ram* hram_, Ppu* ppu_,
          InterruptController* ic_)
      : mbc(mbc_), wram(wram_), hram(hram_), ppu(ppu_), ic(ic_) {}

  u8 read(u16 addr) const override;
  void write(u16 addr, u8 value) override;
  void tick() override;

 private:
  Mbc* mbc;
  Ram* wram;
  Ram* hram;
  Ppu* ppu;
  InterruptController* ic;

  u32 stalls = 0;
  u16 dma_source_address;
  bool is_transfering = false;

  void dma(u8 source);

  void transfer();
};

}  // namespace gbemu

#endif  // GBEMU_BUS_IMPL_H_
