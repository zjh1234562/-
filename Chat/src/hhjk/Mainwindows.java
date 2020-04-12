package hhjk;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.List;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.BindException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.Vector;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.TitledBorder;



public class Mainwindows extends JFrame{
	JFrame frame;
	JTextArea contentArea;
	JTextField txt_message;
	JButton btn_send;	
	JButton btn_history;
	//JButton btn_login;
	JButton btn_sendwj;
	JButton jbt;
	JButton jbt_exit;
	JPanel northPanel;
	JPanel southPanel;
	JScrollPane rightPanel;
	JScrollPane leftPanel;
	JSplitPane centerSplit;
	JList userList;
	DefaultListModel listModel;
	JPopupMenu jPopupMenu;
	JMenuItem jMenuItemadd;
	JMenuItem jMenuItemdelect;
	JMenuItem jMenuItemget;
	boolean isStart = false;
	ClientThraed cThraed;
	ClientThraed2 cThraed2;
	
	
	
	public void writehistory(String str)throws IOException {
		//������ϵ���Ϣд���ļ�------��Ϣ��¼
        FileWriter writer;
        try {
            writer = new FileWriter("history.txt",true);
            writer.write(str);
            writer.flush();
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

	}
	
	public void showMessage(String readLine) {
		//д�����
		contentArea.append(readLine+'\n');
	}



	public void init(String string) {
		//��ʼ��
		frame = new JFrame(string);
		contentArea = new JTextArea();
		contentArea.setEditable(false);
		contentArea.setForeground(Color.blue);
		txt_message = new JTextField();
		btn_send = new JButton("����");	
		btn_history=new JButton("��Ϣ��¼");
		//btn_login=new JButton("��ȡ������Ϣ");
		btn_sendwj=new JButton("�ļ�����");
		jbt=new JButton("��������");
		jbt_exit=new JButton("�˳�");
		jPopupMenu=new JPopupMenu();
		jMenuItemadd=new JMenuItem("��Ӻ���");
		jMenuItemdelect=new JMenuItem("ɾ������");
		jMenuItemget=new JMenuItem("��ȡ��½״̬");
		jPopupMenu.add(jMenuItemadd); //��Ӳ˵���Open
		jPopupMenu.add(jMenuItemdelect);
		jPopupMenu.add(jMenuItemget);
		

		listModel = new DefaultListModel();
		userList = new JList();	

		
		northPanel = new JPanel();
		northPanel.setLayout(new GridLayout(1, 5));
		//northPanel.add(btn_login);
		northPanel.add(btn_history);
		northPanel.add(btn_sendwj);
		northPanel.add(jbt);
		northPanel.add(jbt_exit);
		northPanel.setBorder(new TitledBorder("����ѡ��"));

		southPanel = new JPanel(new BorderLayout());
		southPanel.setBorder(new TitledBorder("д��Ϣ"));
		southPanel.add(txt_message, "Center");
		southPanel.add(btn_send, "East");
		

		leftPanel = new JScrollPane(userList);
		leftPanel.setBorder(new TitledBorder("�����б�"));
		
		rightPanel = new JScrollPane(contentArea);
		rightPanel.setBorder(new TitledBorder("��Ϣ��ʾ��"));

		centerSplit = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, leftPanel,
				rightPanel);
		centerSplit.setDividerLocation(100);

		frame.setLayout(new BorderLayout());
		frame.add(northPanel, "North");
		frame.add(centerSplit, "Center");
		frame.add(southPanel, "South");
		frame.setSize(700, 500);

		//frame.setSize(Toolkit.getDefaultToolkit().getScreenSize());//����ȫ��

		int screen_width = Toolkit.getDefaultToolkit().getScreenSize().width;
		int screen_height = Toolkit.getDefaultToolkit().getScreenSize().height;
		frame.setLocation((screen_width - frame.getWidth()) / 2,
				(screen_height - frame.getHeight()) / 2);
		
		
		frame.setVisible(true);
		
		jMenuItemadd.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				String name=JOptionPane.showInputDialog("��������û�����");
				Mysqljdbc mysqljdbc=new Mysqljdbc();
				mysqljdbc.insert(string, name);
				listModel.addElement(name);
				userList.setModel(listModel);
			}
		});
		
		jMenuItemdelect.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				String name=JOptionPane.showInputDialog("����ɾ���û�����");
				Mysqljdbc mysqljdbc=new Mysqljdbc();
				mysqljdbc.delect(string, name);
				listModel.removeElement(name);
				userList.setModel(listModel);
			}
		});
		
		jMenuItemget.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				try {
					Mysqljdbc mysqljdbc=new Mysqljdbc();
					mysqljdbc.updatedata(string,"T");
					String[]users=mysqljdbc.search(string);
					if (userList.getModel().getSize()==0) {
						for(int i=0;i<users.length;i++) {
							listModel.addElement(users[i]);
						}
						userList.setModel(listModel);
					} else {
						((DefaultListModel)userList.getModel()).removeAllElements();
						for(int i=0;i<users.length;i++) {
							listModel.addElement(users[i]);
							}
						userList.setModel(listModel);

					}
					
					//System.out.println(userList.getModel());
				} catch (Exception e) {
					// TODO: handle exception
				}

			}
		});
		
		userList.addMouseListener(new MouseListener() {
			
			@Override
			public void mouseReleased(MouseEvent arg0) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void mousePressed(MouseEvent arg0) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void mouseExited(MouseEvent arg0) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void mouseEntered(MouseEvent arg0) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void mouseClicked(MouseEvent e) {
				// TODO Auto-generated method stub
		        if(e.getButton() == 3 ) {
		        	jPopupMenu.show(e.getComponent(),e.getX(),e.getY());
		        	
		        }
			}
		});
		
		jbt.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				try {
					cThraed2=new ClientThraed2(Mainwindows.this);
					System.out.println("success");
					cThraed2.start();
					//cThraed2.sendMessage(string2);
						
				} catch (Exception e) {
					// TODO: handle exception
					JOptionPane.showMessageDialog(jbt, "���Ӵ���");
				}
		        
		        
		        
				}
		});
		
		btn_sendwj.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub'
				Object[] options = {"�����ļ�","�����ļ�"};
				int response=JOptionPane.showOptionDialog(null, "��ѡ����", "�ļ�����", JOptionPane.YES_OPTION ,JOptionPane.PLAIN_MESSAGE,
						 null, options, options[0]);
				if (response==0) {
					try {  
			            FileTransferClient fileTransferClient = new FileTransferClient(); // �����ͻ�������  
			            fileTransferClient.sendFile(); // �����ļ�  
			        } catch (Exception e) {  
			            e.printStackTrace();  
			        }  
				}
				else {
					 try {  
				            FileTransferServer server = new FileTransferServer(); // ���������  
				            server.load();  
				        } catch (Exception e) {  
				            e.printStackTrace();  
				        }  
				}
				
				
			}
		});
		
		jbt_exit.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				Mysqljdbc mysqljdbc=new Mysqljdbc();
				mysqljdbc.updatedata(string,"F");
				System.exit(1);
			}
		});
		
		btn_send.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
					try {
						ClientThraed3 clientThraed3=new ClientThraed3(Mainwindows.this);
						String string2=txt_message.getText();
						clientThraed3.start();
						writehistory(string2);
						contentArea.append(string2+'\n');
						txt_message.setText("");
					} catch (Exception e) {
						// TODO: handle exception
					}
					
					
				
				
			}
		});
		

		

		
		btn_history.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				Object[] options = {"��","ɾ��"};
				int response=JOptionPane.showOptionDialog(null, "��ѡ����", "�����¼", JOptionPane.YES_OPTION ,JOptionPane.PLAIN_MESSAGE,
						 null, options, options[0]);
				if (response==0) {
					try {
						BufferedReader brin=new BufferedReader(new FileReader("history.txt"));
						String s;
						while ((s=brin.readLine())!=null) {
							System.out.println(s);
						
						}
					} catch (Exception e) {
						// TODO: handle exception
					}
					
				}
				else {
					try {
						BufferedWriter brWriter=new BufferedWriter(new FileWriter("history.txt"));
						brWriter.write("");
					} catch (Exception e) {
						// TODO: handle exception
					}
					
					
				}
				
				
			}
			
		});
		
	

	}

}
