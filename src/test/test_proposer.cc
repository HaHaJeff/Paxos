#include "proposer.h"


int main()
{
  std::shared_ptr<StateMachine> pState = std::make_shared<StateMachine>();

  Proposer p(pState);
  return 0;
}
