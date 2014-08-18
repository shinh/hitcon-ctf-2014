pneu = File.read('Pneumotoulthamicrescopicfilicoloaganiconissis-df5bb3d8f83d6d37e16560062cb231bc.txt')

pneu[0] = 'm'

pneu.sub!('H', 'i')
pneu.sub!('I', 'y')
pneu.sub!('T', 'e')
pneu.sub!('C', 'r')
pneu.sub!('O', 'l')
pneu.sub!('N', 'y')
pneu.sub!('{', 'l')
pneu.sub!('T', 'g')

[
 ['h', 14037, 't'],
 ['i', 15553, 'a'],
 #
 [' ', 18778, 'y'],
 # f
 ['l', 21917, 'r'],
 ['a', 23566, 's'],
 ['g', 25089, 'l'],
 [' ', 26650, 'l'],
 ['i', 28162, 'l'],
 ['s', 29721, 'l'],
 [' ', 31348, 'r'],
 ['l', 32939, 'a'],
 ['o', 34456, 't'],
 # n
 # g
 # e
 # s
 # t
 # e
 # ??? psenyl 45710 s
 # t ttreonyl
 # e
 # s
 # t
 # e
 # s
 
].each do |c, i, r|
  if pneu[i] != c
    raise
  end
  pneu[i] = r
end

#pneu.sub!(' ', 'y')

pneu.sub!('!', 'a')
pneu.sub!('!', 'a')
pneu.sub!('!', 'i')

pneu.sub!('}', 't')

copy = pneu.dup
$rep = []

def repl(pneu, x)
  pneu.gsub!(x, '')
  $rep << x
end

def last(c)
  x = c.dup
  $rep.each do |r|
    x.gsub!(r, '_' * r.size)
  end
  puts x
end

repl(pneu, 'acetylseryl')
#copy.gsub!('acetylseryl', '_')
repl(pneu, 'glutaminyl')
#copy.gsub!('glutaminyl', '_')
repl(pneu, 'aspartyl')
#copy.gsub!('aspartyl', '_')
repl(pneu, 'iso')
#copy.gsub!('iso', '_')
#repl(pneu, 'isoleucyl')
repl(pneu, 'tryptophyl')
#copy.gsub!('tryptophyl', '_')

while true
  prev = 0
  ps = 0
  4.upto(99) do |l|
    s = pneu.scan(pneu[0, l]).size
    v = s * l
    if v < prev
      if s == 1
        puts pneu
        exit
      end

      if v < 40
        puts pneu
        #puts copy
        exit
      end

      l -= 1
      s = pneu.scan(pneu[0, l]).size
      v = s * l
      STDERR.puts "#{pneu[0, l]} #{l}*#{s}=#{v} #{pneu.size}"
      repl(pneu, pneu[0, l])
      #copy.gsub!(pneu[0, l], '_')
      STDERR.puts "#{pneu[0,16]}..."
      break
    end

    prev = v

    if l == 99
      puts pneu
      last(copy)
      #puts copy
      exit
    end
  end

end

# pneu.gsub!(/Methiony/i)
# pneu.gsub!('lthreony')
# pneu.gsub!('glutaminyl')
# pneu.gsub!('larginyl')
# pneu.gsub!('tyrosyl')
# pneu.gsub!('glutamyl')
# pneu.gsub!('seryl')
# pneu.gsub!('leucyl')



puts pneu
exit

m = {}
pneu.chars.each do |c|
  m[c] = 0 if !m[c]
  m[c] += 1
end

m.sort_by{|x, y|-y}.each do |x, y|
  puts "#{x} #{y}"
end

puts pneu[10921 + 1500, 200]
puts pneu[10921 + 3000, 400]

