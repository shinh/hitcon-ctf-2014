#!/usr/bin/env ruby

skipto = nil
skipto = '496_solve'

if skipto
  f = skipto
else
  f = 'tarmful-3f13b82f7794de783adfd6fa9928ad2c.zip'

  system("rm -fr /tmp/work")
  system("mkdir -p /tmp/work")
  system("cp #{f} /tmp/work")
end

Dir.chdir("/tmp/work")

while true
  type = `file #{f}`
  if f =~ /\.zip/ || type =~ /Zip archive/
    o = `unzip #{f}`
    puts o

    f = o[/(extracting|inflating): (.*)/, 2].strip

    #f = o[/extracting: (.*\.zip)/, 1]
    #if !f
    #  f = o[/inflating: (.*\.tar\.(bz2|gz))/, 1]
    #end
  elsif f =~ /\.tar\..*/ || type =~ /bzip2|gzip/
    pipe = IO.popen(['tar', '-xvf', f])
    o = pipe.read
    pipe.close
    puts o

    #f = o[/^\d+\/\d+\.(tar\.|zip).*/]
    f = o[/^.*\Z/]

    f.gsub!(/\\\\/, '\\')
  else
    raise "Unknown file type #{f}"
  end

  n = f.tr("/\\: `'\"()<>", '___________')
  n.gsub!(/\W/, '_')
  n.gsub!(/\\/, '_')
  n.sub!(/;.*/, '')

  puts "#{f} => #{n}"
  File.rename(f, n)
  f = n

  if !File.exist?(f)
    raise f
  end
end
