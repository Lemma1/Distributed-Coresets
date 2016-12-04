#ifndef WORKER_H
#define WORKER_H

#include "data.h"

#include <mpi.h>
#include <unordered_map>

struct Shared_mem_float{
  MPI_Win win;
  float *ptr;
};

class CSET_Worker{
public:
	int m_rank;
	int m_num_slots;
	int m_num_parameters;
  int m_slot_size;
  Shared_mem_int m_shared_table;
  Shared_mem_float m_shared_slots;
  CSET_Data *m_data;
  std::unordered_map<int, int> m_slot_info;

	CSET_Worker(const int &rank, const int &num_slots, 
              const int &num_parameters, const int& slot_size,
              Shared_mem_int shared_table,  
              Shared_mem_float shared_slots,
              CSET_Data *data);
	~CSET_Worker();
  int lock_all();
  int update_info();
  int edit_file_info(const int &file_idx, const int &status, 
                        const int& count);
  int edit_table_info(const int &slot_idx, const int &status, 
                        const int& rank, const int& level);
  int unlock_all();
  int get_slot_info();
  int evolve();
};


#endif