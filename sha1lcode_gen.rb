#!/usr/bin/env ruby

require 'digest'

('aaaaaaaa'..'zzzzzzzz').each do |s|
  s = s * 2
  dig = Digest::SHA1.hexdigest(s)
  #p dig
  #if dig !~ /^ffc0eb10/
  #if dig !~ /^eb24/
  #if dig !~ /^eb23/
  #if dig !~ /0f05$/
  if dig !~ /^0f05/
    next
  end

  tmp = '/tmp/b'
  File.open(tmp, 'w') do |of|
    of.print dig.chars.each_slice(2).map{|c|c.join.hex.chr}.join
  end

  dump = `objdump -b binary -m i386:x86-64 -D #{tmp}`
  #if dump =~ /\(bad\)|\.byte|fwait|lahf|icebp|vminpd|call|ret/
  #  next
  #end

  puts "=== #{s} ==="
  puts dump
end

