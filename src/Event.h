#pragma once

#include "GeneMachineTag.h"

enum class EventType : uint8_t {
  PieceIdentified, // we know what's in this reader's slot
  PieceRemoved     // a nucleotide piece has left this slot
};

struct Event {
  EventType type;
  uint8_t slot;
  gene_tag::NucleotidePair pair;
};

using EventCallback = void (*)(const Event &);
