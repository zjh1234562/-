package hhjk;

import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
 
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.WindowConstants;

public class LoginPanell extends JFrame {
	JLabel jl1;
	JLabel jl2;
	
	public void init() {
		setTitle("���½");
		setLayout(null);
		// ����һ������
		Container c = getContentPane();
		// ����"�û���:"��ǩ
		jl1 = new JLabel("�û�����");
		// �����ı���
		final JTextField jtf1 = new JTextField();
		// ����"����:"��ǩ
		jl2 = new JLabel("����:");
		// ���������
		final JPasswordField jpf1 = new JPasswordField();
		// ���������ַ�Ϊ*
		jpf1.setEchoChar('*');
		// ����"�ύ"��ť
		JButton jb1 = new JButton("�ύ");
		// ����"����"��ť
		JButton jb2 = new JButton("����");
		jb1.addActionListener(new ActionListener() {
 
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				
					if (((jtf1.getText().trim().equals("С��") && new String(jpf1.getPassword()).trim().equals("mrsoft")))
							||((jtf1.getText().trim().equals("С��") && new String(jpf1.getPassword()).trim().equals("mrsoft")))
							||((jtf1.getText().trim().equals("С��") && new String(jpf1.getPassword()).trim().equals("mrsoft")))) {
						JOptionPane.showMessageDialog(null, "��½�ɹ���");
						destory();
						Mainwindows mainwindows=new Mainwindows();
						mainwindows.init(jtf1.getText());
						
					} else if (jtf1.getText().trim().length() == 0 || new String(jpf1.getPassword()).trim().length() == 0) {
						JOptionPane.showMessageDialog(null, "����Ϊ��!");
					} else {
						JOptionPane.showMessageDialog(null, "����");
						// ����
						jtf1.setText("");
						jpf1.setText("");
					}
					

			}
		});
		// ʵ��"����"��ť����
		jb2.addActionListener(new ActionListener() {
 
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				jtf1.setText("");
				jpf1.setText("");
 
			}
		});
		// ���������ӵ�������
		c.add(jl1);
		c.add(jtf1);
		c.add(jl2);
		c.add(jpf1);
		c.add(jb1);
		c.add(jb2);
		// ���ø������λ���Լ���С
		jl1.setBounds(10, 20, 90, 30);
		jtf1.setBounds(60, 20, 210, 30);
		jl2.setBounds(25, 60, 90, 30);
		jpf1.setBounds(60, 60, 210, 30);
		jb1.setBounds(80, 100, 60, 40);
		jb2.setBounds(150, 100, 60, 40);
		// ���ô����С���رշ�ʽ����������
		setSize(300, 220);
		setVisible(true);
		setResizable(true);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		//return jtf1.getText();
		
	}	
	
	public void destory() {
		setVisible(false);
	}

	public static void main(String[] args) {
		LoginPanell loginPanel=new LoginPanell();
		loginPanel.init();
		
	}

}
