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

import java.net.Socket;

import java.net.UnknownHostException;

public class ClientThraed extends Thread{

	DataInputStream input;
	DataOutputStream out;
    Mainwindows client;
    FileInputStream fis;
    DataOutputStream dos; 
   	public static final String IP_ADDR = "localhost";//服务器地址 
   	public static final int PORT = 12334;//服务器端口号
   	

	public ClientThraed(Mainwindows client) throws UnknownHostException, IOException {
		//Socket socket=new Socket(IP_ADDR,PORT);
		//input = new DataInputStream(socket.getInputStream()); 
		//out = new DataOutputStream(socket.getOutputStream()); 
		this.client=client;
	}

	public void sendMessage(String text) throws IOException {
		//String str = new BufferedReader(new InputStreamReader(System.in)).readLine();
		out.writeUTF(text); 
		//out.close();
		
	}
	
	



	@Override

	public void run() {

	while(true)

	{

		try {
			Socket socket=new Socket(IP_ADDR,PORT);
			input = new DataInputStream(socket.getInputStream()); 
			out = new DataOutputStream(socket.getOutputStream()); 

			client.showMessage("接收到信息：                             "+input.readUTF());
			out.close();
			input.close();
			
			//sendFile(socket);
			


		} catch (Exception e) {

			// TODO Auto-generated catch block

			e.printStackTrace();

		}	

	}

	}

}
