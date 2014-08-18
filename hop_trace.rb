#!/usr/bin/env ruby

pipe = IO.popen(['gdb', 'hop'], 'r+')

pipe.puts 'b hop.cc:78'
#pipe.puts "run BITCON{01234567890123456789012345678901}"
pipe.puts "run HITCON{01234567890123456789012345678901}"
pipe.puts "p argv[1]"

done = false
while !done
  pipe.puts 'si'
  pipe.puts 'disas $rip,$rip+1'
  pipe.puts 'p $rax'
  pipe.puts 'p "marKer"'

  while l = pipe.gets
    if l =~ /marKer/
      break
    end

    puts l

    if l =~ /printf/
      pipe.puts 'cont'
      done = true
      break
    end
  end
end

pipe.close_write
puts pipe.read

