# Embracing Packet Loss in TCP Congestion Control 

* a network packet is a formatted unit of data carried by a packet-switched network. A packet consists of control information and user data; the latter is also known as the payload. Control information provides data for delivering the payload.

* TCP (Transmission Control Protocol) is a standard that defines how to establish and maintain a network conversation through which application programs can exchange data. TCP works with the Internet Protocol (IP), which defines how computers send packets of data to each other.

* Packet loss occurs when one or more packets of data travelling across a computer network fail to reach their destination. Packet loss is either caused by errors in data transmission, typically across wireless networks, or network congestion.

* TCP uses a network congestion-avoidance algorithm that includes various aspects of an additive increase/multiplicative decrease scheme, along with other schemes including slow start and congestion window, to achieve congestion avoidance.

* Reno: if three duplicate ACKs are received, Reno will perform a fast retransmit and skip the slow start phase by instead halving the congestion window, setting the slow start threshold equal to the new congestion window, and enter a phase called fast recovery.

* Cubic: TCP CUBIC default in Linux, most popular TCP for popular Web servers.it's increase TCP’s sending rate until packet loss occurs at some router’s output: the bottleneck link.

![](https://i.ibb.co/3m3XnvH/Screenshot-from-2020-12-23-18-21-29-1.png)

In this project I used these algorithms to measure how long it takes them to accurately detect the packet losses with creating sockets using TCP protocol and CC algorithms in c language.
I also used 'tc' (Traffic Control) to packet loss of 10%, 15%, 20%, 25% and 30% by sending a 1MB file and here are the results:

| Packet Loss | Cubic CC AVG Time | Reno CC AVG Time|
| -- | --| -- | 
| 0% | 1.002093 sec|1.002233 sec| 
| 10% |1.084104 sec|1.95328 sec| 
| 15% | 1.084104 sec| 3.182702 sec| 
| 20% | 6.844125 sec|8.352214 sec| 
| 25% | 18.392849 sec| 14.452283 sec| 
| 30% | 42.182998 sec| 64.535568 sec| 

![](https://i.ibb.co/wc4rxcW/Embracing-Packet-Loss-in-TCP-Congestion-Control.png)
