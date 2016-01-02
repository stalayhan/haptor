#ifndef __utils_h__
#define __utils_h__

extern int errno = 0;

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
#define check_mem(A) check((A), "Out of memory.")
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL -1

#define CHUNK 1024 /* read 1024 bytes at a time */
#define SAMPLE_FILE_NAME "rssi_samples.csv"
#define DELIM ","

#define NUMBER_OF_ROUTER 3
#define RSSI_SAMPLE_SIZE 200

#define ARDUINO_PORT 24
#define BAUDRATE 115200
#define MAX_BUFF_SIZE 4095
#define MIN_BUFF_SIZE 80

struct router{
  char channel;
  char rssi;  // keep positive, check sender code, if doesn't send positive, multipyly -1
  char bssid; // map to the router so don't have to keep 17 char (size of mac address) each router
};

struct direction{
  int northDegree;  // the angle relative to the north 0-360 - 16bit
  int turnDegree;
};

/*
* unsigned long = 32 bit -  0 - 4,294,967,295
*
* Packet size = 32*2 = 64 bits - 8 bytes
*/
struct gps_coord{
  unsigned long x_coord;
  unsigned long y_coord;
};

/**
 *
 * Packet size = (3 + 2 + 8 + 2) = 15 chars for all requirements.
 */
struct payload{
  struct router st_router;
  struct direction st_direction;
  struct gps_coord st_gps_coord;
  char type;  // packet type e.g. indoor_pos_resp_t, indoor_pos_req_t
  char flag;  // for feature development
  char checksum;
};

#if 0
typedef struct{
	int rssi_values[NUMBER_OF_ROUTER]; /* 3 router means 3 rssi values */
	int class2;	 	/* if class value is -1 no class yet */
	double distance;	/* distance from the new value */
}rssi_keeper;
#endif // 0

#endif

