#!/usr/bin/env ruby

require 'socket'

class Float
  def to_i
    self.floor
  end
end

def solve_impl(a)
  if a.size == 1
    #if `python -c 'print abs(eval("#{a[0][1]}") - 24) >= 1e-15'` =~ /False/
    #  raise a[0][1]
    #end
    if (a[0][0] - 24.0).abs < 1e-15
      raise a[0][1]
    elsif (a[0][0] + 24.0).abs < 1e-15
      raise "-(#{a[0][1]})"
    end
    return
  end

  a.size.times{|i|
    i.times{|j|
      n = a[0,j] + a[j+1..i-1] + a[i+1..-1]
      solve_impl(n + [[a[j][0] + a[i][0], "(#{a[j][1]}+#{a[i][1]})"]])
      solve_impl(n + [[a[j][0] - a[i][0], "(#{a[j][1]}-#{a[i][1]})"]])
      solve_impl(n + [[a[i][0] - a[j][0], "(#{a[i][1]}-#{a[j][1]})"]])
      solve_impl(n + [[a[j][0] * a[i][0], "(#{a[j][1]}*#{a[i][1]})"]])
      solve_impl(n + [[a[j][0] * -a[i][0], "(#{a[j][1]}*-#{a[i][1]})"]])
      solve_impl(n + [[a[j][0] ** a[i][0], "(#{a[j][1]}**#{a[i][1]})"]])
      solve_impl(n + [[a[i][0] ** a[j][0], "(#{a[i][1]}**#{a[j][1]})"]])
      solve_impl(n + [[a[j][0] ** -a[i][0], "(#{a[j][1]}**-#{a[i][1]})"]])
      solve_impl(n + [[a[i][0] ** -a[j][0], "(#{a[i][1]}**-#{a[j][1]})"]])
      if a[i][0] != 0
        solve_impl(n + [[a[j][0] / a[i][0], "(#{a[j][1]}/#{a[i][1]})"]])
        solve_impl(n + [[a[j][0] / -a[i][0], "(#{a[j][1]}/-#{a[i][1]})"]])
        solve_impl(n + [[a[i][0] / a[j][0], "(#{a[i][1]}/#{a[j][1]})"]])
        solve_impl(n + [[a[i][0] / -a[j][0], "(#{a[i][1]}/-#{a[j][1]})"]])
        if a[i][0] != Float::INFINITY && a[j][0] != Float::INFINITY
          if a[i][0].to_i != 0
            solve_impl(n + [[(a[j][0] / a[i][0]).to_i.to_f,
                             "(#{a[j][1]}//#{a[i][1]})"]])
            solve_impl(n + [[(a[j][0] / -a[i][0]).to_i.to_f,
                             "(#{a[j][1]}//-#{a[i][1]})"]])
          end
          if a[j][0].to_i != 0
            solve_impl(n + [[(a[i][0] / a[j][0]).to_i.to_f,
                             "(#{a[i][1]}//#{a[j][1]})"]])
            solve_impl(n + [[(a[i][0] / -a[j][0]).to_i.to_f,
                             "(#{a[i][1]}//-#{a[j][1]})"]])
          end
        end
      end
    }
  }
end


#solve_impl([8, 6, 11, 12].map{|v|[v.to_f, v.to_s]})
#solve_impl([13, 13, 4, 1].map{|v|[v.to_f, v.to_s]})
#exit

def solve(a)
  begin
    solve_impl(a)
    puts 'no anser...'
  rescue
    return $!
  end
  return '13//13**(-1/4)'
end

s = TCPSocket.new('210.65.89.59', 2424)

while l = s.gets
  puts l
  if l =~ /Question .*?: (\[.*?\])/
    q = eval($1)
    a = solve(q.map{|v|[v.to_f, v.to_s]})
    puts a
    s.puts("#{a}")
  end
end

#q = [13, 9, 9, 3]
# q = [9, 7, 8, 2]
# # 9 7 8 2
# solve(q.map{|v|[v.to_f, v.to_s]})
