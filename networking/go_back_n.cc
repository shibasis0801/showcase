#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

#define repeat(i, start, end) for (int i = start; i < end; ++i)

struct GBN {

  int total_data;
  int window_size;
  double probability_threshold;

  bool should_reach() {
    double p = rand() / (double) RAND_MAX;
    return p < probability_threshold;
  }

  GBN(int total_data, int window_size, double probability_threshold) : total_data(total_data), window_size(window_size), probability_threshold(probability_threshold)
  {
    srand(time(0));
  }

  struct SenderState  {
    int base_seqno;
    int next_seqno;

    int cumulative_ack;
    void acknowledge(int ack_value) {
      cumulative_ack = ack_value;
    }

    SenderState(int base, int next, int cumulative_ack): base_seqno(base), next_seqno(next), cumulative_ack(cumulative_ack)
    {}
  };

  struct RecieverState {
    int ackd_seqno;

    vector<int> packets;
    void send(vector<int> packet_seqnos) {
      packets = packet_seqnos;
    }

    RecieverState(int ackd_seqno): ackd_seqno(ackd_seqno) {
      packets = vector<int>(0);
    }
  };


  void sender(SenderState &sender, RecieverState &reciever) {

    vector<int> packets;
    int cumulative_ack = sender.cumulative_ack;
    int base = sender.base_seqno;

    if (cumulative_ack == -1 || cumulative_ack != base + window_size) {


      repeat(next, base, base + window_size) {
        if (should_reach())
          packets.push_back(next);
      }

      reciever.send(packets);

      repeat(i, 0, packets.size()) {
        cout << packets[i] << ',';
      }
      cout << endl;
    }
    else {
      sender.base_seqno = sender.cumulative_ack;
      sender.next_seqno = sender.cumulative_ack;
    }

    if (sender.base_seqno == total_data) {
      exit(0);
    }
  }

  void reciever(SenderState &sender, RecieverState &reciever) {

    if ( ! reciever.packets.empty() ) {
      int i;
      int ack;
      int size = reciever.packets.size();

      for(i = 0; i < size; ++i) {
        int seq_no = reciever.packets[i];

        if(i) {
          if ( seq_no - ack != 1)
            break;
        }
        ack = seq_no;
      }
      ack += 1;
      sender.acknowledge(ack);
      cout << "ACK: " << ack << endl;
      if (i == size)
        reciever.packets = vector<int>(0);
    }
  }

  void simulate() {
    bool sender_turn = true;

    SenderState senderState( 0, 0, -1);
    RecieverState recieverState(-1);

    while (true) {

      if (sender_turn)
        sender(senderState, recieverState);
      else
        reciever(senderState, recieverState);

      sender_turn = ! sender_turn;

    }
  }

};

int main() {
  GBN gbn(100, 10, 0.6);
  gbn.simulate();
}
