#include "SequenceManager.h"

void SequenceManager::handleEvent(const Event &event) {
  printEvent(event);
  switch (event.type) {
  case EventType::PieceIdentified:
    slots_[event.slot] = event.pair;
    // check if all slots have been filled
    // mark sequence_complete_ as true here, the following check will revert it
    // back to false if ANY of the slots are empty
    sequence_complete_ = true;
    for (int i = 0; i < config::NUM_READERS; i++) {
      if (slots_[i] == gene_tag::NucleotidePair::None) {
        sequence_complete_ = false;
        break;
      }
    }

    if (sequence_complete_) {
      Serial.println("Slots filled!");
      printSequence();
      uint8_t index = buildSequenceIndex();
      Serial.print("Sending UDP packet: {");
      Serial.print(config::VIDEO_COMMANDS[index]);
      Serial.println(" }\n");
      ethernet_.sendUdpCommand(config::VIDEO_COMMANDS[index]);
    }
    break;
  case EventType::PieceRemoved:
    slots_[event.slot] = gene_tag::NucleotidePair::None;
    sequence_complete_ = false;
    break;
  default:
    break;
  }
}

void SequenceManager::printSequence() {
  Serial.print("Sequence order: ");
  for (int i = 0; i < config::NUM_READERS; i++) {
    Serial.print(gene_tag::pairToString(slots_[i]));
  }
  Serial.println();
}

void SequenceManager::printEvent(const Event &event) {
  switch (event.type) {
  case EventType::PieceIdentified:
    Serial.print(gene_tag::pairToString(event.pair));
    Serial.print(" Nucleotide pair placed in slot: ");
    Serial.println(event.slot);
    break;
  case EventType::PieceRemoved:
    Serial.print("Piece removed from slot: ");
    Serial.println(event.slot);
    break;
  default:
    break;
  }
}

uint8_t SequenceManager::buildSequenceIndex() {
  uint8_t index = 0;
  for (int i = 0; i < config::NUM_READERS; i++) {
    if (slots_[i] == gene_tag::NucleotidePair::CG) {
      index |= (1 << i);
    }
  }
  return index;
}
