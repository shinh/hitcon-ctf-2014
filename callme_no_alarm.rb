#!/usr/bin/env ruby
# -*- coding: binary -*-

c = File.open('callme-69d26b77eb41e4eeba1d7b8402a8b165', 'r:binary').read
#STDERR.puts c[0x68f, 5].inspect
c[0x71c,5] = "\x90" * 5
c[0x73e,5] = "\x90" * 5
File.open('callme-hack', 'w:binary') do |of|
  of.print(c)
end
system("chmod 755 callme-hack")
