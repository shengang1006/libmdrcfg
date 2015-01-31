#������ָ��������·��
CC      := g++

AR := ar rc

# args
BITS = 32

#������ָ����Ҫ�Ŀ��ļ� -L
LIBS    := -lrt

#������ָ��������Ҫ��ͷ�ļ�
INCLUDE := -I./

#������lib·��
LIBPATH := 


#������Դ�ļ�
SRCS    := *.cpp

#������ָ��Ŀ���ļ� ���е�.cpp�ļ����.o�ļ�
OBJS    := $(SRCS:.cpp=.o)


#�����Ǳ���ѡ��
CFLAGS  := -g -Wall -c $(INCLUDE) $(LIBPATH) 
CFLAGS  += -DLINUX 

ifeq ($(BITS),64)
	TARGETLIB := libmdrcfg64.a
else
	TARGETLIB := libmdrcfg.a
endif

all:
	$(CC) $(CFLAGS) $(SRCS) $(LIBS)
	$(AR) $(TARGETLIB) $(OBJS) 
#make clean ɾ�����е�.o�ļ�
clean:
	rm -f ./*.o
