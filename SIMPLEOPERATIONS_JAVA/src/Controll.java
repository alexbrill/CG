import org.apache.commons.math3.util.FastMath;

public class Controll {
	
	final static int VIEW_DIMENSION = 2;
	final static int FIGURE_DIMENSION = 3;
	
	static double[][] rotationAxis = {{400, 30, 0}, {400, 60, 0}};
	
	static double[][] figure = {
			{0, 0, 0, 1},
			{0, 0, 100, 1},
			{0, 100, 0, 1},
			{0, 100, 100, 1},
			{100, 0, 0, 1},
			{100, 0, 100, 1},
			{100, 100, 0, 1},
			{100, 100, 100, 1}};
	
	static int[][] squares = {
			{0, 1, 5, 4},
			{0, 1, 3, 2},
			{1, 3, 7, 5},
			{0, 4, 6, 2},
			{2, 3, 7, 6},
			{4, 5, 7, 6},
			{1, 3, 5, 7}};
	
	static Cube m;
	
	public Controll() {
		m = new Cube(figure);
		m.move(400, 290, 0);
	}
	
	public static int[][] getViewMatrix(double[][] matrix) {
		int[][] viewMatrix = new int[matrix.length][];
		
		for (int i = 0, j; i < matrix.length; i++) {
			viewMatrix[i] = new int[VIEW_DIMENSION];
			for (j = 0; j < VIEW_DIMENSION; j++) {
				viewMatrix[i][j] = (int)Math.round(matrix[i][j]);
			}
		}		
		
		return viewMatrix;
	}
	
	public void changeRotationAxis(double[][] newRotationAxis) {
		rotationAxis = newRotationAxis;
	}
	
	public void rotateFigure(int axis, double angle) {
		int curRotationAxis = (axis + 1) % FIGURE_DIMENSION;
				
		m.move(-rotationAxis[0][0], -rotationAxis[0][1], -rotationAxis[0][2]);
		
		int count = 0;
		double rotAngle = 0;
		
		while(count != 5) {			
			switch(curRotationAxis) {
			case 0: //x
				rotAngle = (count == 2)?angle:FastMath.atan2(rotationAxis[1][2] - rotationAxis[0][2], //z1-z0
															rotationAxis[1][1] - rotationAxis[0][1]); //y1-y0
				if (count < 2) rotAngle *= -1;
				m.rotateX(rotAngle);				
				break;
			case 1: //y
				rotAngle = (count == 2)?angle:FastMath.atan2(rotationAxis[1][2]- rotationAxis[0][2], //z1-z0
															rotationAxis[1][0] - rotationAxis[0][0]); //x1-x0
				if (count < 2) rotAngle *= -1;
				m.rotateY(rotAngle);
				break;
			case 2: //z
				rotAngle = (count == 2)?angle:FastMath.atan2(rotationAxis[1][0] - rotationAxis[0][0], //x1-x0
															rotationAxis[1][1] - rotationAxis[0][1]); //y1-y0
				if (count < 2) rotAngle *= -1;
				m.rotateZ(rotAngle);
				break;
			}

			
			if (count < 2) curRotationAxis = (curRotationAxis + 1) % FIGURE_DIMENSION;
			else curRotationAxis = (curRotationAxis - 1 + FIGURE_DIMENSION) % FIGURE_DIMENSION;
			
			count++;
		}				
		
		m.move(rotationAxis[0][0], rotationAxis[0][1], rotationAxis[0][2]);
	}
	
	public int[][] getLinesToDraw() {
		
		/*Cube newCube = new Cube(m.getMatrix());
		newCube.move(-450, -340, -50);
		newCube.perspectiveTransform();
		newCube.move(450, 340, 50);*/
		
		
		int[][] viewMatrix = getViewMatrix(m.getMatrix());		
		int amountLinesToDraw = squares.length * squares[0].length + 1; 
		int[][] linesToDraw = new int[amountLinesToDraw][squares[0].length];
		
		for (int i = 0, j, n = 0; i < squares.length; i++) {
			for (j = 0; j < squares[i].length; j++) {
				
				int ind_p1 = squares[i][j];
				int ind_p2 = squares[i][(j+1)%squares[i].length];				
				
				linesToDraw[n++] = new int[] {viewMatrix[ind_p1][0], viewMatrix[ind_p1][1],
										viewMatrix[ind_p2][0], viewMatrix[ind_p2][1]};
				
			}
		}
		
		 
		
		linesToDraw[amountLinesToDraw-1] = new int[] {(int)rotationAxis[0][0], (int)rotationAxis[0][1],
														(int)rotationAxis[1][0], (int)rotationAxis[1][1]};
		
				
		return linesToDraw;
	}
	
	
	/*public static void main(String[] args) {
		Controll c = new Controll();	
		m = new Cube(figure);
		v = new View(c);
				
		m.rotateX(20);
		m.rotateZ(15);
		m.rotateY(20);
		m.move(200, 200, 0);
		
		
		int[][] viewMatrix = getViewMatrix(m.getMatrix());
		
		int amountLinesToDraw = squares.length * squares[0].length + 1;
		int[][] linesToDraw = new int[amountLinesToDraw][squares[0].length];
		
		for (int i = 0, j, n = 0; i < squares.length; i++) {
			for (j = 0; j < squares[i].length; j++) {
				
				int ind_p1 = squares[i][j];
				int ind_p2 = squares[i][(j+1)%squares[i].length];				
				
				linesToDraw[n++] = new int[] {viewMatrix[ind_p1][0], viewMatrix[ind_p1][1],
										viewMatrix[ind_p2][0], viewMatrix[ind_p2][1]};
				
			}
		}
		
		 
		
		linesToDraw[amountLinesToDraw-1] = new int[] {(int)rotationAxis[0][0], (int)rotationAxis[0][1],
														(int)rotationAxis[1][0], (int)rotationAxis[1][1]};
		
		v.drawArea.setToDraw(linesToDraw);	
		
		
	}*/
}
