#������ָ��������·��
CC      := g++

AR := ar rc

# args

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

TARGETLIB := libmdrcfg.a

all:
	$(CC) $(CFLAGS) $(SRCS) $(LIBS)
	$(AR) $(TARGETLIB) $(OBJS) 
#make clean ɾ�����е�.o�ļ�
clean:
	rm -f ./*.o
