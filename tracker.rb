require 'rubygems'
require 'serialport'
require 'net/http'
require 'uri'
require 'nokogiri'
require 'date'

#Variables for Train arrival time
train_coming = 2
last_chance = 2

url = "http://lapi.transitchicago.com/api/1.0/ttarrivals.aspx?max=1&mapid=41020&key=" 
key = "9ad8747a976447b78ee0fa2f0a0d68c2"

while true do

  #Get the next arrival time
  uri = URI.parse(url+key)
  http = Net::HTTP.new(uri.host, uri.port)
  request = Net::HTTP::Get.new(uri.request_uri)
  response = http.request(request)
  response_doc = Nokogiri::XML(response.body)
  arrival_time = response_doc.xpath("//arrT").first.text

  #Format the time
  format_arrival_time = DateTime.strptime(arrival_time,  "%Y%d%m  %H:%M:%S")

  #Set up serial communication
  sp = SerialPort.new '/dev/ttyACM0', 9600

  #Determine if approaching time is "catchable"
  if format_arrival_time.min < (DateTime.now.min + 15) && format_arrival_time.min > (DateTime.now.min - 10) 
    sp.write "#{train_coming}"
    #Last chance to leave!
    if format_arrival_time.min < (DateTime.now.min + 10)
      sp.write "#{last_chance}"
    end
  end
  sleep 10
end
