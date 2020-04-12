package hhjk;


import java.io.BufferedReader;
import java.io.DataOutputStream;  
import java.io.File;  
import java.io.FileInputStream; 

import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;

import java.io.InputStreamReader;

import java.io.OutputStreamWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;

import java.net.UnknownHostException;

import com.mysql.jdbc.PacketTooBigException;

public class ClientThraed2 extends Thread{

    Mainwindows client;
   	

	public ClientThraed2(Mainwindows client) throws UnknownHostException, IOException { 
		this.client=client; 
	}

	public void receiveMessage() throws IOException {
        DatagramSocket socket = new DatagramSocket(10002);
        while(true){
            byte[] arr = new byte[1024];

            DatagramPacket packet = new DatagramPacket(arr,arr.length);

            socket.receive(packet);

            String content = new String(packet.getData(),0,packet.getLength());
            String ip = packet.getAddress().getHostAddress();
            //System.out.println(ip+"  "+content);
            client.contentArea.append("接收到来自ip:"+ip+"        "+content+'\n');
        }
        
		
	}
	
	@Override

	public void run() {
		try{
			receiveMessage();
        }
        catch(Exception e){
            System.out.println("找不到发送方");
        }

	}

}
