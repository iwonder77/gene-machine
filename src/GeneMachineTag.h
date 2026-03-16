/**
 * Gene Machine — Tag Data Format
 *
 * Shared header defining the NFC tag data format used by the
 * Gene Sequencing Machine museum exhibit.
 *
 * Used by both the exhibit firmware and the technician writer tool.
 *
 * Tag data layout (4 bytes, one NTAG213 page starting at page 4):
 *   Byte 0: Magic (0x67) — identifies tag as belonging to this exhibit
 *   Byte 1: Format revision (0x01)
 *   Byte 2: Nucleotide pair (0x01 = AT, 0x02 = CG)
 *   Byte 3: XOR checksum of bytes 0–2
 */

#pragma once
#include <Arduino.h>

namespace gene_tag {

// -- Constants --------------------------------------------------------

constexpr uint8_t MAGIC_BYTE = 0x67;
constexpr uint8_t REV_BYTE = 0x01;

// -- Types ------------------------------------------------------------

enum class NucleotidePair : uint8_t { NONE = 0, AT = 1, CG = 2 };

// NOTE: no padding in this struct since all four fields are uint8_t.
struct TagData {
  uint8_t magic;
  uint8_t rev;
  NucleotidePair pair;
  uint8_t checksum;
};

// --- Functions --------------------------------------------------------
// Marked inline because they are defined in a header.

inline uint8_t calculateChecksum(const uint8_t *data, uint8_t length) {
  uint8_t sum = 0;
  for (uint8_t i = 0; i < length; i++) {
    sum ^= data[i];
  }
  return sum;
}

inline const char *pairToString(NucleotidePair pair) {
  switch (pair) {
  case NucleotidePair::AT:
    return "AT";
  case NucleotidePair::CG:
    return "CG";
  default:
    return "UNKNOWN";
  }
}

/**
 * Parse tag data from a raw byte buffer.
 * Validates magic byte and checksum.
 *
 * The TagData struct `out` is always populated via memcpy, even if buffer data
 * doesn't match, so it is up to the caller to inspect individual fields for
 * diagnostics.
 */
inline bool parseTagData(const byte *buffer, TagData &out) {
  memcpy(&out, buffer, sizeof(TagData));

  if (out.magic != MAGIC_BYTE) {
    return false;
  }

  uint8_t expected = calculateChecksum((uint8_t *)&out, sizeof(out) - 1);
  return expected == out.checksum;
}

} // namespace gene_tag
