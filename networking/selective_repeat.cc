#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

#define repeat(i, start, end) for (int i = start; i < end; ++i)
#define all(v) (v).begin(), (v).end()

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

    vector<int> unacknowledged_packets;
    void acknowledge(vector<int> packets, int window_size) {
      unacknowledged_packets = vector<int>(0);

      for (int packet : packets) {
          remove(unacknowledged_packets.begin(), unacknowledged_packets.end(), packet);
      }

    }

    SenderState(int base, int next, int window_size): base_seqno(base), next_seqno(next) {

      repeat(i, 0, window_size)
          unacknowledged_packets.push_back(i);
    }
  };

  struct RecieverState {
    int ackd_seqno;
    vector<int> recieved_packets;
    void send(vector<int> packets) {
      recieved_packets = packets;
    }


    RecieverState(int ackd_seqno): ackd_seqno(ackd_seqno) {
      recieved_packets = vector<int>(0);
    }
  };


  void sender(SenderState &sender, RecieverState &reciever) {

    vector<int> packets;

    int base = sender.base_seqno;

    if ( ! sender.unacknowledged_packets.empty() ) {
      for(int packet : sender.unacknowledged_packets) {
        if (should_reach())
          packets.push_back(packet);
      }
      reciever.send(packets);

      cout << "\nSent: ";
      for(int packet : packets)
        cout << packet << ',';

      cout << endl;
    }
    else {
      sender.base_seqno += window_size;
      sender.next_seqno += window_size;
    }

    if (sender.base_seqno == total_data) {
      exit(0);
    }
  }

  void reciever(SenderState &sender, RecieverState &reciever) {

    if ( ! reciever.recieved_packets.empty() ) {

      cout << "ACK: ";
      for(int packet : reciever.recieved_packets)
        cout << packet << ',';

      sender.acknowledge(reciever.recieved_packets, window_size);

      if (reciever.recieved_packets.size() == window_size)
        reciever.recieved_packets = vector<int>(0);
    }
  }

  void simulate() {
    bool sender_turn = true;

    SenderState senderState( 0, 0, window_size);
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
  GBN gbn(100, 10, 0.69);
  gbn.simulate();
}
