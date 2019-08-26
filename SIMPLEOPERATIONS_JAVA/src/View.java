import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;

public class View extends JFrame {
	
	public static final Dimension WND_SIZE = new Dimension(900, 680);
	public static final Dimension DRAWAREA_SIZE = new Dimension(680, 680);
	public static final Dimension INPUTPANEL_SIZE = new Dimension(190, 120);
	public static final String WND_TITLE = "3D GRAPHIC ROTATION";		
	
	Controll controll;
	DrawArea drawArea;
	AxisInputPanel axisInputPanel;
	AngleInputPanel angleInputPanel;
	
	
	public View() {		
		super(WND_TITLE);
		setPreferredSize(WND_SIZE);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);		
		setLayout(null);
		getContentPane().setBackground(Color.GRAY);
		
		controll = new Controll();
				
		drawArea = new DrawArea();		
		add(drawArea);		

		drawArea.setToDraw(controll.getLinesToDraw());
		
		axisInputPanel = new AxisInputPanel();
		add(axisInputPanel);
		
		angleInputPanel = new AngleInputPanel();
		add(angleInputPanel);
				
		pack();
		setVisible(true);
	}
	
	class DrawArea extends JComponent {
		
		int[][] toDraw = {};
		
		public DrawArea() {
			setPreferredSize(DRAWAREA_SIZE);
			setBounds(0, 0, DRAWAREA_SIZE.width, DRAWAREA_SIZE.height);
			getContentPane().setBackground(Color.white);
		}
		
		 public void paintComponent(Graphics g){
			    super.paintComponents(g); 
			    Graphics2D g2d = (Graphics2D)g;
			    g2d.clearRect(0, 0, WND_SIZE.width, WND_SIZE.height);
			    g2d.setColor(Color.BLACK);
			    g2d.clipRect(0, 0, DRAWAREA_SIZE.width, DRAWAREA_SIZE.height);

			    for (int i = 0; i < toDraw.length; ++i)
			    	g2d.drawLine(toDraw[i][0], toDraw[i][1], toDraw[i][2], toDraw[i][3]);			    
		 }
		 
		 public void setToDraw(int[][] arg0) {
			 toDraw = arg0;
			 super.repaint();
		 }
	}
	
	class AxisInputPanel extends JPanel {
		
		JTextField field_P1X;
		JTextField field_P1Y;
		JTextField field_P1Z;
		
		JTextField field_P2X;
		JTextField field_P2Y;
		JTextField field_P2Z;
		
		
		public AxisInputPanel() {
			setPreferredSize(INPUTPANEL_SIZE);
			setBounds(DRAWAREA_SIZE.width + 10, 100, INPUTPANEL_SIZE.width, INPUTPANEL_SIZE.height);
			setLayout(new GridBagLayout());
			GridBagConstraints c = new GridBagConstraints(); 			
			c.fill = GridBagConstraints.HORIZONTAL;
			
			c.gridwidth = 3;
			c.gridx = 0; c.gridy = 0;						
			JLabel txt_P1 = new JLabel("P1 (X, Y, Z)");
			add(txt_P1, c);
			c.gridy = 2;
			JLabel txt_P2 = new JLabel("P2 (X, Y, Z)");
			add(txt_P2, c);
			c.gridy = 4;
			JButton btn_ok = new JButton("OK");
			add(btn_ok, c);			
			
			c.gridwidth = 1;
			c.gridx = 0; c.gridy = 1;				
			field_P1X = new JTextField(5);
			add(field_P1X, c);			
			c.gridx = 1;
			field_P1Y = new JTextField(5);
			add(field_P1Y, c);			
			c.gridx = 2;
			field_P1Z = new JTextField(5);			
			add(field_P1Z, c);
			c.gridx = 0; c.gridy = 3;				
			field_P2X = new JTextField(5);
			add(field_P2X, c);			
			c.gridx = 1;
			field_P2Y = new JTextField(5);
			add(field_P2Y, c);			
			c.gridx = 2;
			field_P2Z = new JTextField(5);			
			add(field_P2Z, c);		
			
			btn_ok.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent arg0) {
					//Double.parseDouble
					
					try {
						double p1x = Double.parseDouble(field_P1X.getText());
						double p1y = Double.parseDouble(field_P1Y.getText());
						double p1z = Double.parseDouble(field_P1Z.getText());
						double p2x = Double.parseDouble(field_P2X.getText());
						double p2y = Double.parseDouble(field_P2Y.getText());
						double p2z = Double.parseDouble(field_P2Z.getText());
					
						controll.changeRotationAxis(new double[][]{{p1x, p1y, p1z}, {p2x, p2y, p2z}});
						drawArea.setToDraw(controll.getLinesToDraw());
					}
					catch (NumberFormatException e) {
						System.out.println("FAILED"); //!!!!!!!!!! TO DO
					}
				}
			});
		}
		
		
	}
	
	class AngleInputPanel extends JPanel {
		JTextField field_angle;
		ButtonGroup group;
		JRadioButton btn_X, btn_Y, btn_Z;
		
		public AngleInputPanel() {
			setPreferredSize(INPUTPANEL_SIZE);
			setBounds(DRAWAREA_SIZE.width + 10, 320, INPUTPANEL_SIZE.width, INPUTPANEL_SIZE.height);
			setLayout(new GridBagLayout());
			GridBagConstraints c = new GridBagConstraints(); 
			c.fill = GridBagConstraints.HORIZONTAL;
			
			c.gridwidth = 3;
			c.gridx = 2; c.gridy = 0;	
			field_angle = new JTextField(5);
			add(field_angle, c);
			c.gridy = 2;
			JButton btn_ok = new JButton("OK");
			add(btn_ok, c);	
			
			c.gridwidth = 1;
			c.gridx = 0; c.gridy = 0;
			btn_X = new JRadioButton("x");
			btn_X.setSelected(true);
			add(btn_X, c);
			c.gridy = 1;
			btn_Y = new JRadioButton("y");
			add(btn_Y, c);
			c.gridy = 2;
			btn_Z = new JRadioButton("z");
			add(btn_Z, c);
			
			group = new ButtonGroup();
			group.add(btn_X);
			group.add(btn_Y);
			group.add(btn_Z);
			
			btn_ok.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent arg0) {
					
					try {
						double angle = Double.parseDouble(field_angle.getText());
					
						if (btn_X.isSelected()) {
							controll.rotateFigure(0, angle);
						}
						else if (btn_Y.isSelected()) {
							controll.rotateFigure(1, angle);
						}
						else if (btn_Z.isSelected()) {
							controll.rotateFigure(2, angle);
						}
						
						drawArea.setToDraw(controll.getLinesToDraw());
					}
					catch (NumberFormatException e) {
						System.out.println("FAILED"); //!!!!!!!!!! TO DO
					}					
						
				}
			});
		}
	}
	
	
	public static void main(String[] args) {
		View v = new View();
		
		
		
		
	}
}
