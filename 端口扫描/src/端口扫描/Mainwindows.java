package 端口扫描;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JMenu;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JRadioButton;
import javax.swing.JButton;
import javax.swing.JSlider;
import java.awt.Font;
import javax.swing.JProgressBar;
import java.awt.Color;
import java.awt.TextArea;
import javax.swing.JSeparator;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.sql.Time;
import java.util.HashSet;
import java.util.Set;

import javax.swing.JDesktopPane;
import javax.swing.JToggleButton;
import javax.swing.JTable;
import javax.swing.JSplitPane;
import javax.swing.JToolBar;
import javax.swing.SwingUtilities;
import javax.swing.JInternalFrame;
import 端口扫描.ShowProgressBar;

public class Mainwindows {

	private JFrame frame;
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;
	private JTextField textField_3;
	private JTextField textField_4;
	//JRadioButton radioButton_1;
	private TextArea textArea;
	public boolean radioButton_select=false;    //刚开始都没选中
	public boolean radioButton_1_select=false;
	private JTextField textField_5;
	int n=0;//记录当前扫描的端口数目
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Mainwindows window = new Mainwindows();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Mainwindows() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setTitle("\u7AEF\u53E3\u626B\u63CF\u5668");
		frame.setBounds(100, 100, 760, 690);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		JMenuBar menuBar = new JMenuBar();
		menuBar.setBounds(0, 0, 773, 23);
		frame.getContentPane().add(menuBar);
		
		JMenu menu = new JMenu("Help");
		menuBar.add(menu);
		
		JMenu menu_1 = new JMenu("\u4F7F\u7528\u624B\u518C");
		menu.add(menu_1);
		
		JLabel label = new JLabel("\u8BF7\u8F93\u5165IP\u5730\u5740");
		label.setBounds(10, 45, 77, 29);
		frame.getContentPane().add(label);
		
		textField = new JTextField();
		textField.setColumns(10);
		textField.setBounds(97, 49, 108, 22);
		frame.getContentPane().add(textField);
		
		JRadioButton radioButton = new JRadioButton("\u67E5\u627E\u5355\u4E2A\u7AEF\u53E3");
		radioButton.setBounds(330, 22, 121, 23);
		frame.getContentPane().add(radioButton);
		
		JRadioButton radioButton_1 = new JRadioButton("\u67E5\u627E\u7AEF\u53E3\u8303\u56F4");
		radioButton_1.setBounds(330, 76, 121, 23);
		frame.getContentPane().add(radioButton_1);
		
		radioButton.addMouseListener(new MouseListener() {
			
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
			public void mouseClicked(MouseEvent arg0) {
				// TODO Auto-generated method stub
				if (radioButton_1.isSelected()==true) {
					radioButton.setSelected(false);
					JOptionPane.showMessageDialog(radioButton, "不能同时选两个");
				}
			}
		});
		
		radioButton_1.addMouseListener(new MouseListener() {
			
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
			public void mouseClicked(MouseEvent arg0) {
				// TODO Auto-generated method stub
				if (radioButton.isSelected()==true) {
					radioButton_1.setSelected(false);
					JOptionPane.showMessageDialog(radioButton_1, "不能同时选两个");
				}
				
			}
		});
		
		JLabel label_1 = new JLabel("\u8BF7\u8F93\u5165\u7AEF\u53E3\u53F7");
		label_1.setBounds(330, 45, 77, 29);
		frame.getContentPane().add(label_1);
		
		textField_1 = new JTextField();
		textField_1.setColumns(10);
		textField_1.setBounds(429, 49, 66, 22);
		frame.getContentPane().add(textField_1);
		
		JButton button = new JButton("Refresh");
		button.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				textField_1.setText("");
				textField_2.setText("");
				textField_3.setText("");
				textField_4.setText("");
				textField_5.setText("");
				textField.setText("");
				radioButton.setSelected(false);
				radioButton_1.setSelected(false);
			}
		});
		button.setBounds(618, 40, 103, 38);
		frame.getContentPane().add(button);
		
		textField_2 = new JTextField();
		textField_2.setColumns(10);
		textField_2.setBounds(429, 101, 66, 22);
		frame.getContentPane().add(textField_2);
		
		JLabel label_2 = new JLabel("\u8BF7\u8F93\u5165\u7AEF\u53E3\u8303\u56F4");
		label_2.setBounds(330, 100, 91, 29);
		frame.getContentPane().add(label_2);
		
		textField_3 = new JTextField();
		textField_3.setColumns(10);
		textField_3.setBounds(501, 101, 66, 22);
		frame.getContentPane().add(textField_3);
		
		textField_4 = new JTextField();
		textField_4.setColumns(10);
		textField_4.setBounds(186, 97, 66, 22);
		frame.getContentPane().add(textField_4);
		
		JLabel label_3 = new JLabel("\u8BF7\u8F93\u5165\u6BCF\u4E2A\u8FDB\u7A0B\u5904\u7406\u7684\u7AEF\u53E3\u6570");
		label_3.setBounds(10, 95, 180, 29);
		frame.getContentPane().add(label_3);
		
		JSlider slider = new JSlider();
		slider.setValue(100);
		slider.setEnabled(false);
		slider.setBounds(0, 128, 734, 11);
		frame.getContentPane().add(slider);
		
		JLabel label_4 = new JLabel("\u626B\u63CF\u7ED3\u679C");
		label_4.setFont(new Font("宋体", Font.BOLD, 12));
		label_4.setBounds(14, 137, 91, 25);
		frame.getContentPane().add(label_4);
		
		JProgressBar progressBar = new JProgressBar();
		progressBar.setToolTipText("");
		progressBar.setStringPainted(true);
		progressBar.setForeground(Color.GREEN);
		Font font=new Font("宋体", Font.BOLD, 12);
		progressBar.setFont(font);
		progressBar.setBackground(Color.white);
		progressBar.setBounds(10, 521, 579, 21);
		//ShowProgressBar showProgressBar=new ShowProgressBar(progressBar);
		frame.getContentPane().add(progressBar);
		
		TextArea textArea = new TextArea();
		textArea.setEditable(false);
		textArea.setFont(new Font("宋体", Font.BOLD, 12));
		//textArea.setText("端口号                  开放状态                  类型\n");
		textArea.setBackground(Color.WHITE);
		textArea.setBounds(12, 181, 577, 324);
		frame.getContentPane().add(textArea);
		
		JButton button_1 = new JButton("Run");
		button_1.addMouseListener(new MouseListener() {
			
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
			public void mouseClicked(MouseEvent arg0) {
				// TODO Auto-generated method stub
				String startip=textField.getText();
				String endip=textField_5.getText();
				String threadnums=textField_4.getText();
				int threadn=1;
				if (threadnums.length()!=0) {
					threadn=Integer.parseInt(threadnums);
				}
				int startport=0;
				int endport=0;
				//new ShowProgressBar(progressBar).start();
				if (radioButton.isSelected()==true) {
					String string1=textField_1.getText();
					//int i1=0;
					if (string1.length()==0) {
						JOptionPane.showMessageDialog(button_1, "请输入端口号");
					}else {
						startport = Integer.parseInt(string1);
						endport=startport;
						if (startport<1||startport>65535) {
							JOptionPane.showMessageDialog(button_1, "端口范围错误，请输入1-65535");
						}
					}
					//new ScanPort(textArea,progressBar).startscan(i1,i1,startip,threadn);
				}else {
					String string2=textField_2.getText();
					String string3=textField_3.getText();
					//int i3=0;
					//int i2=0;
					if (string2.length()==0||string3.length()==0) {
						JOptionPane.showMessageDialog(button_1, "请输入端口号");
					}
					else {
						startport = Integer.parseInt(string2);
						endport = Integer.parseInt(string3);
						if (startport<1||startport>65535||endport<1||endport>65535) {
							JOptionPane.showMessageDialog(button_1, "端口范围错误，请输入1-65535");
						}
						if (startport>endport) {
							JOptionPane.showMessageDialog(button_1, "起始端口要小于结束端口");
						}
						//new ScanPort(textArea,progressBar).startscan(i2,i3,startip,threadn);
					}	
				}
				String mess=new IsIP().testIp(startip, endip);
				if(mess=="IP地址不能为空！") {
					JOptionPane.showMessageDialog(button_1, "IP地址不能为空！");
				}else if (mess=="IP地址段开始部分不能为空！") {
					JOptionPane.showMessageDialog(button_1, "IP地址段开始部分不能为空！");
				}else if (mess=="你输入的IP地址格式不正确！") {
					JOptionPane.showMessageDialog(button_1, "你输入的IP地址格式不正确！");
				}
				int portsize=endport-startport;
				Set<String> ipSet = new HashSet<String>();//IP的集合
				if(endip.length()==0) {
					new IsIP().scanIp(startip, startip, ipSet);
					//new ScanPort(textArea, progressBar,n).startscan(startport, endport, startip, threadn);
				}
				else {
					new IsIP().scanIp(startip, endip, ipSet);
				}
				int maxnum=portsize*ipSet.size();
				progressBar.setMaximum(maxnum);
			    new ShowProgressBar(progressBar,maxnum).start();
			    //new ShowProgressBar(progressBar,maxnum);
				for (String ipString:ipSet) {
					new ScanPort(textArea, progressBar,n).startscan(startport, endport, ipString, threadn);
					textArea.append("所用线程数："+portsize/threadn+'\n');
					textArea.append("-----------------------------------------------------------------------\n");
				}
			}
		});
		button_1.setBounds(618, 211, 103, 38);
		frame.getContentPane().add(button_1);
		
		JButton button_2 = new JButton("Empty");
		button_2.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				textArea.setText("");
			}
		});
		button_2.setBounds(618, 308, 103, 38);
		frame.getContentPane().add(button_2);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(487, 110, 17, 21);
		frame.getContentPane().add(separator);
		
		JDesktopPane desktopPane = new JDesktopPane();
		desktopPane.setBounds(173, 269, 77, -20);
		frame.getContentPane().add(desktopPane);
		
		textField_5 = new JTextField();
		textField_5.setColumns(10);
		textField_5.setBounds(215, 49, 108, 22);
		frame.getContentPane().add(textField_5);
		
		JSeparator separator_1 = new JSeparator();
		separator_1.setBounds(201, 60, 17, 21);
		frame.getContentPane().add(separator_1);
	}
}
