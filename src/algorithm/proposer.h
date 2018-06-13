#ifndef PROPOSER_H
#define PROPOSER_H

//TODO: need mutex?
//TODO: persist
class ProposerState {
  public:
    ProposerState() : maxRound_(0), nextIndex_(0), prepared_(false) {  }
    ~ProposerState() {  }

    void SetMaxRound(int round) { maxRound_ = round; }
    void IncMaxRound() { maxRound_ += 1; }
    uint32_t GetMaxRound() const { return maxRound_; }

    void SetNextIndex(int index) { nextIndex_ = index; }
    uint32_t GetNextIndex() const { return nextIndex_; }

    bool IsPrepared() { return prepared_; }
    void SetPrepared() { prepared_ = true; }
    void SetNotPrepared() { prepared_ = false; }

  private:
    uint32_t firstUnchosenIndex_;
    uint32_t maxRound_;
    uint32_t nextIndex_;
    bool prepared_;
};

class Proposer {
  public:
    Proposer();
    ~Proposer();

    void SendPrepare(const PrepareRequest &request, PrepareReply &reply);
    void SendAccept(const AcceptRequest &request, AcceptReply &reply);
    void SendSuccess(const SuccessRequest &request, SuccessReply &reply);

  private:
    void NewPrepareRequest(PreapreRequest &request);
    void NewAcceptReuqest(AcceptRequest &request);
    void NewSuccessRequest(SuccessRequest &request);

  private:
    ProposerState state_;
};

#endif
