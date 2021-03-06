#ifndef BLOCK_SYNC_H_
#define BLOCK_SYNC_H_

#include <map>
#include <vector>

#include "src/ascii_in.h"
#include "config.h"
#include "src/groups.h"
#include "src/subcarrier.h"

namespace redsea {

uint32_t calcSyndrome(uint32_t vec);
eOffset offsetForSyndrome(uint16_t syndrome);
eOffset nextOffsetFor(eOffset o);
uint32_t correctBurstErrors(uint32_t block, eOffset offset);

class BlockStream {
 public:
  BlockStream(Options options);
  Group getNextGroup();
  bool isEOF() const;
#ifdef DEBUG
  float getT() const;
#endif

 private:
  int getNextBit();
  void uncorrectable();
  bool acquireSync();

  unsigned bitcount_;
  unsigned prevbitcount_;
  int left_to_read_;
  uint32_t wideblock_;
  unsigned prevsync_;
  unsigned block_counter_;
  eOffset expected_offset_;
  eOffset received_offset_;
  uint16_t pi_;
  bool is_in_sync_;
  std::vector<bool> block_has_errors_;
#ifdef HAVE_LIQUID
  Subcarrier subcarrier_;
#endif
  AsciiBits ascii_bits_;
  const eInputType input_type_;
  bool is_eof_;
};

} // namespace redsea
#endif // BLOCK_SYNC_H_
