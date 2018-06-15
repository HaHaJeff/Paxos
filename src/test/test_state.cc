#include "state.h"

int main()
{
  StateMachine sm;

  ProposalEntry proposal1 = std::pair<uint32_t, std::string>(100, "Add");
  LogEntry entry1 = std::pair<uint32_t, ProposalEntry>(0,proposal1);

  ProposalEntry proposal2 = std::pair<uint32_t, std::string>(102, "Del");
  LogEntry entry2 = std::pair<uint32_t, ProposalEntry>(1,proposal2);

  ProposalEntry proposal3 = std::pair<uint32_t, std::string>(110, "Sub");
  LogEntry entry3 = std::pair<uint32_t, ProposalEntry>(2,proposal3);

  ProposalEntry proposal4 = std::pair<uint32_t, std::string>(150, "Mod");
  LogEntry entry4 = std::pair<uint32_t, ProposalEntry>(3,proposal4);

  ProposalEntry proposal5 = std::pair<uint32_t, std::string>(151, "Mul");
  LogEntry entry5 = std::pair<uint32_t, ProposalEntry>(4,proposal5);

  ProposalEntry proposal6 = std::pair<uint32_t, std::string>(154, "Toy");
  LogEntry entry6 = std::pair<uint32_t, ProposalEntry>(5,proposal6);

  sm.AddToStateMachine(entry1);
  sm.Print();
  sm.AddToStateMachine(entry2);
  sm.Print();
  sm.AddToStateMachine(entry3);
  sm.Print();
  sm.AddToStateMachine(entry4);
  sm.Print();
  sm.AddToStateMachine(entry5);
  sm.Print();
  sm.AddToStateMachine(entry6);
  sm.Print();
  return 0;
}
