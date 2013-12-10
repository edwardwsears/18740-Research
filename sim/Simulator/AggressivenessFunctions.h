//added
#define NUM_METRICS 5
#define ACC_INDEX 0
#define LAT_INDEX 1
#define POL_INDEX 3
#define COV_INDEX 3
#define BND_INDEX 4
//param defines
#define LOW_ACC -1
#define MED_ACC 0
#define HIGH_ACC 1
#define HIGH true
#define LOW false
//decision defines
#define DEC -1
#define NOC 0
#define INC 1

// FIRST ORDER PREFETCHERS BEGIN
int ComputeAggressiveness0(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC: return DEC; break;
		case MED_ACC: return NOC; break;
		case HIGH_ACC: return INC; break;
		default: return NOC; break;
	}

}

int ComputeAggressiveness1(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(pollute){
		case LOW: return INC; break;
		case HIGH: return DEC; break;
	}

}

int ComputeAggressiveness2(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(mem_band){
		case LOW: return DEC; break;
		case HIGH: return INC; break;
	}

}

// FIRST ORDER PREFETCHERS END

// SECOND OREDER PREFETCHERS BEGIN

int ComputeAggressiveness3(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(late){
				case LOW: return DEC; break;
				case HIGH: return DEC; break;
			}
			break;
		case MED_ACC:
			switch(late){
				case LOW: return INC; break;
				case HIGH: return DEC; break;
			}
			break;
		case HIGH_ACC:
			switch(late){
				case LOW: return NOC; break;
				case HIGH: return INC; break;
			}
		default: return NOC; break;
	}

}  

int ComputeAggressiveness4(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(coverage){
				case LOW: return DEC; break;
				case HIGH: return DEC; break;
			}
			break;
		case MED_ACC:
			switch(coverage){
				case LOW: return INC; break;
				case HIGH: return NOC; break;
			}
			break;
		case HIGH_ACC:
			switch(coverage){
				case LOW: return INC; break;
				case HIGH: return NOC; break;
			}
		default: return NOC; break;
	}

}

int ComputeAggressiveness5(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(pollute){
				case LOW: return DEC; break;
				case HIGH: return DEC; break;
			}
			break;
		case MED_ACC:
			switch(pollute){
				case LOW: return INC; break;
				case HIGH: return DEC; break;
			}
			break;
		case HIGH_ACC:
			switch(pollute){
				case LOW: return NOC; break;
				case HIGH: return INC; break;
			}
		default: return NOC; break;
	}

}
                           
int ComputeAggressiveness6(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(mem_band){
				case LOW: return DEC; break;
				case HIGH: return INC; break;
			}
			break;
		case MED_ACC:
			switch(mem_band){
				case LOW: return DEC; break;
				case HIGH: return INC; break;
			}
			break;
		case HIGH_ACC:
			switch(mem_band){
				case LOW: return NOC; break;
				case HIGH: return INC; break;
			}
		default: return NOC; break;
	}

}

int ComputeAggressiveness7(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(late){
		case LOW:
			switch(coverage){
				case LOW: return INC; break;
				case HIGH: return NOC; break;
			}
			break;
		case HIGH:
			switch(coverage){
				case LOW: return DEC; break;
				case HIGH: return INC; break;
			}
			break;
	}

}

int ComputeAggressiveness8(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(late){
		case LOW:
			switch(pollute){
				case LOW: return NOC; break;
				case HIGH: return DEC; break;
			}
			break;
		case HIGH:
			switch(pollute){
				case LOW: return INC; break;
				case HIGH: return DEC; break;
			}
			break;
	}


}

int ComputeAggressiveness9(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(late){
		case LOW:
			switch(mem_band){
				case LOW: return NOC; break;
				case HIGH: return INC; break;
			}
			break;
		case HIGH:
			switch(mem_band){
				case LOW: return DEC; break;
				case HIGH: return INC; break;
			}
			break;
	}


}

int ComputeAggressiveness10(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(coverage){
		case LOW:
			switch(pollute){
				case LOW: return INC; break;
				case HIGH: return DEC; break;
			}
			break;
		case HIGH:
			switch(pollute){
				case LOW: return NOC; break;
				case HIGH: return DEC; break;
			}
			break;
	}


}

int ComputeAggressiveness11(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(coverage){
		case LOW:
			switch(mem_band){
				case LOW: return DEC; break;
				case HIGH: return INC; break;
			}
			break;
		case HIGH:
			switch(mem_band){
				case LOW: return DEC; break;
				case HIGH: return NOC; break;
			}
			break;
	}


}

int ComputeAggressiveness12(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(pollute){
		case LOW:
			switch(mem_band){
				case LOW: return DEC; break;
				case HIGH: return INC; break;
			}
			break;
		case HIGH:
			switch(mem_band){
				case LOW: return DEC; break;
				case HIGH: return DEC; break;
			}
			break;
	}


}

// SECOND ORDER PREFETCHERS END

// THIRD ORDER PREFETCHERS BEGIN

int ComputeAggressiveness13(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW: return DEC; break; 
						case HIGH: return DEC; break;
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		case MED_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW: return INC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		case HIGH_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW: return INC; break;
						case HIGH: return NOC; break;
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW: return INC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness14(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW: return DEC; break; 
						case HIGH: return DEC; break;
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW: return NOC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		case MED_ACC:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW: return INC; break;
						case HIGH: return DEC; break;
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW: return NOC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		case HIGH_ACC:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW: return INC; break;
						case HIGH: return DEC; break;
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW: return NOC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}

}

int ComputeAggressiveness15(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(pollute){
				case LOW:
					switch(mem_band){
						case LOW: return DEC; break; 
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		case MED_ACC:
			switch(pollute){
				case LOW:
					switch(mem_band){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		case HIGH_ACC:
			switch(pollute){
				case LOW:
					switch(mem_band){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness16(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(late){
		case LOW:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW: return INC; break; 
						case HIGH: return DEC; break;
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW: return NOC; break;
						case HIGH: return DEC;
					}
					break;
			}
			break;
		case HIGH:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW: return INC; break;
						case HIGH: return DEC; break;
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW: return INC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness17(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(late){
		case LOW:
			switch(coverage){
				case LOW:
					switch(mem_band){
						case LOW: return DEC; break; 
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		case HIGH:
			switch(coverage){
				case LOW:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return INC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness18(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(late){
				case LOW:
					switch(pollute){
						case LOW: return NOC; break; 
						case HIGH: return DEC; break;
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW: return DEC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		case MED_ACC:
			switch(late){
				case LOW:
					switch(pollute){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		case HIGH_ACC:
			switch(late){
				case LOW:
					switch(pollute){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW: return INC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness19(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(late){
				case LOW:
					switch(mem_band){
						case LOW: return DEC; break; 
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		case MED_ACC:
			switch(late){
				case LOW:
					switch(mem_band){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		case HIGH_ACC:
			switch(late){
				case LOW:
					switch(mem_band){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return INC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness20(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(coverage){
				case LOW:
					switch(mem_band){
						case LOW: return DEC; break; 
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		case MED_ACC:
			switch(coverage){
				case LOW:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		case HIGH_ACC:
			switch(coverage){
				case LOW:
					switch(mem_band){
						case LOW: return INC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness21(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(late){
		case LOW:
			switch(pollute){
				case LOW:
					switch(mem_band){
						case LOW: return NOC; break; 
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		case HIGH:
			switch(pollute){
				case LOW:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return INC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness22(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(coverage){
		case LOW:
			switch(pollute){
				case LOW:
					switch(mem_band){
						case LOW: return DEC; break; 
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		case HIGH:
			switch(pollute){
				case LOW:
					switch(mem_band){
						case LOW: return NOC; break;
						case HIGH: return INC; break;
					}
					break;
				case HIGH:
					switch(mem_band){
						case LOW: return DEC; break;
						case HIGH: return DEC; break;
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

// THIRD ORDER PREFETCHERS END

// FOURTH ORDER PREFETCHERS BEGIN

int ComputeAggressiveness23(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW: return NOC; break;
								case HIGH: return DEC; break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW: return NOC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW: return NOC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;

			}
			break;
		case MED_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW: return INC; break;
								case HIGH: return DEC; break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW: return INC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW: return INC; break;
								case HIGH: return DEC; break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW: return INC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;

			}
			break;
		case HIGH_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW: return INC; break;
								case HIGH: return DEC; break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW: return NOC; break;
								case HIGH: return NOC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW: return INC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW: return INC; break;
								case HIGH: return NOC; break;
							}
							break;					
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness24(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;					
					}
					break;

			}
			break;
		case MED_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;					
					}
					break;

			}
			break;
		case HIGH_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(mem_band){
								case LOW: return INC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return INC; break;
								case HIGH: return INC; break;
							}
							break;					
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness25(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(late){
		case LOW:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;

			}
			break;
		case HIGH:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return INC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;					
					}
					break;

			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness26(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(late){
				case LOW:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;

			}
			break;
		case MED_ACC:
			switch(late){
				case LOW:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return INC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;

			}
			break;
		case HIGH_ACC:
			switch(late){
				case LOW:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return NOC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return NOC; break;
							}
							break;					
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

int ComputeAggressiveness27(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return NOC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return DEC; break;
							}
							break;					
					}
					break;

			}
			break;
		case MED_ACC:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return NOC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return NOC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return INC; break;
							}
							break;					
					}
					break;

			}
			break;
		case HIGH_ACC:
			switch(coverage){
				case LOW:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return INC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return NOC; break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(pollute){
						case LOW:
							switch(mem_band){
								case LOW: return NOC; break;
								case HIGH: return NOC; break;
							}
							break;
						case HIGH:
							switch(mem_band){
								case LOW: return DEC; break;
								case HIGH: return NOC; break;
							}
							break;					
					}
					break;
			}
			break;
		default: return NOC; break;
	}


}

// FOURTH ORDER PREFETCHERS END

// FIFTH ORDER PREFETCHERS BEGIN

int ComputeAggressiveness28(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	switch(accuracy){
		case LOW_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW:
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH:
 									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW:
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH:
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW:
 									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW:
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;					
					}
					break;

			}
			break;
		case MED_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW:
									switch(mem_band){
										case LOW: return NOC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH:
 									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW: 
									switch(mem_band){
										case LOW: return INC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW:
									switch(mem_band){
										case LOW: return NOC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;					
					}
					break;

			}
			break;
		case HIGH_ACC:
			switch(late){
				case LOW:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW: 
									switch(mem_band){
										case LOW: return INC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH:
 									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW:
									switch(mem_band){
										case LOW: return NOC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return DEC; break;
									}
									break;
							}
							break;					
					}
					break;
				case HIGH:
					switch(coverage){
						case LOW:
							switch(pollute){
								case LOW:
									switch(mem_band){
										case LOW: return INC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return INC; break;
									}
									break;
							}
							break;
						case HIGH:
							switch(pollute){
								case LOW: 
									switch(mem_band){
										case LOW: return INC; break;
										case HIGH: return INC; break;
									}
									break;
								case HIGH: 
									switch(mem_band){
										case LOW: return DEC; break;
										case HIGH: return INC; break;
									}
									break;
							}
							break;					
					}
					break;
			}
			break;
		default: return NOC; break;
	}

}

// FIFTH ORDER PREFETCHERS END
