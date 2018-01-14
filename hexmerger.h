static const int SUCCESS = 0;
static const int IO_ERROR = -1;

static const int HEADER_START = 49;
static const int HEADER_END = 64;
static const int HEADER_MAX_VALUE = 1024;
static const int HEADER_GAP = 3*16;
static const int HEADER_LEN = HEADER_END - HEADER_START +1;

void print_usage();
int merge(const char* file1, const char* file2, const char* destinationFile);
bool is_header_section(int pos);