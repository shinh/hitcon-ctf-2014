# N = 99999
# a = []
# N.times{
#   a << rand(3)
# }

N = 99999
a = []
N.times{
  a << rand(2**63) - 2 ** 62
}

puts N
puts a * ' '
puts
puts '__INPUT__'
puts a.sort[N/2]
puts
puts '__OUTPUT__'
