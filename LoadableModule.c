Test - A test loadable Module
#
#
# Author: Gricelle
#.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
obj-m := test.o

#obj-m+=test.o

all:
        make -C /lib/project/$(shell uname -r)/build/ M=$(PWD) modules

clean:
        make -C /lib/project/$(shell uname -r)/build/ M=$(PWD) clean



#strip --strip-unneeded test.ko
