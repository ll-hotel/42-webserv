srcs := Client.cpp Socket.cpp Worker.cpp WorkerEntry.cpp

SRCS += $(addprefix worker/,$(srcs))
