#----------------------------------------------------------------------
# logs
#----------------------------------------------------------------------
LOG_ERROR = lambda *args: print('error:', *args)
LOG_WARNING = lambda *args: print('warning:', *args)
LOG_INFO = lambda *args: print('info:', *args)
LOG_DEBUG = lambda *args: print('debug:', *args)
LOG_VERBOSE = lambda *args: print('debug:', *args)

# ignore log levels
LOG_VERBOSE = lambda *args: 0
LOG_DEBUG = lambda *args: 0