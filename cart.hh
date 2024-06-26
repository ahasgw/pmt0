#ifndef CART_HH_
#define CART_HH_ 1

#include "node.hh"

#include <iosfwd>
#include "ptcl.hh"
#include "timer.hh"

class CartNode: public WorkNode {
 private:
  v3r div_min;
  v3r div_max;
  v3r sys_size;
  v3r sys_min;
  v3r sys_max;
  v3i cart_pos;
  Ptcls ptcls;
  Ptcls recv_buff[26];  // buffers are used in order of arrival
  Timer t_comm;
  Timer t_step;
  Timer t_init;
  const Conf &conf_;
  std::ostream *os;
  MPI_Comm cart_comm;
  int cart_rank;
  int cart_size;
  int steps_to_write;

  enum { MIDDLE_DIR = 0x00, LOWER_DIR = 0x02, UPPER_DIR = 0x03 };
  struct Connect {
    unsigned dir_tag;
    int send_to;
    int recv_from;
    MPI_Request req;
  };
  typedef std::vector<Connect> Conns;
  Conns conns;  // elements are sorted by dir_tag

 public:
  CartNode(const Conf &conf);
  ~CartNode();

  void StepForward(int t);

 private:
  void InitConnect();
  void GenerateParticles();
  void ExchangeParticles();
};

#endif  // CART_HH_
