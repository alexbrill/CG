import org.apache.commons.math3.linear.MatrixUtils;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.util.FastMath;

public class Cube {
	
	RealMatrix matrix;	
	
	public Cube(double[][] figure) {
		matrix = MatrixUtils.createRealMatrix(figure);
		
	}
	
	public void rotateZ(double angle) {
		double cosA = FastMath.cos(FastMath.toRadians(angle));
		double sinA = FastMath.sin(FastMath.toRadians(angle));
		
		RealMatrix rotationMatrix = MatrixUtils.createRealMatrix(new double[][] {
				{cosA, sinA, 0, 0},
				{-sinA, cosA, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}});	
		
		matrix = matrix.multiply(rotationMatrix);		
	}
	
	public void rotateX(double angle) {
		double cosA = FastMath.cos(FastMath.toRadians(angle));
		double sinA = FastMath.sin(FastMath.toRadians(angle));
		
		RealMatrix rotationMatrix = MatrixUtils.createRealMatrix(new double[][] {
				{1, 0, 0, 0},
				{0, cosA, sinA, 0},
				{0, -sinA, cosA, 0},
				{0, 0, 0, 1}});
		
		matrix = matrix.multiply(rotationMatrix);	
	}

	public void rotateY(double angle) {
		double cosA = FastMath.cos(FastMath.toRadians(angle));
		double sinA = FastMath.sin(FastMath.toRadians(angle));
		
		RealMatrix rotationMatrix = MatrixUtils.createRealMatrix(new double[][] {
				{cosA, 0, -sinA, 0},
				{0, 1, 0, 0},
				{sinA, 0, cosA, 0},
				{0, 0, 0, 1}});
		
		matrix = matrix.multiply(rotationMatrix);	
	}
	
	public void move(double x, double y, double z) {		
		RealMatrix moveMatrix = MatrixUtils.createRealMatrix(new double[][] {
															{1, 0, 0, 0},
															{0, 1, 0, 0},
															{0, 0, 1, 0},
															{x, y, z, 1}});	
		
		matrix = matrix.multiply(moveMatrix);
	}
	
	public void perspectiveTransform() {
		RealMatrix perspectiveMatrix = MatrixUtils.createRealMatrix(new double[][] {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, -0.001},
			{0, 0, 0, 1}});
		
		matrix = matrix.multiply(perspectiveMatrix);
		
		int ind = matrix.getColumnDimension() - 1;
		
		for (int i = 0, j; i < matrix.getRowDimension(); i++)
			for (j = 0; j < matrix.getColumnDimension() - 1; j++)
				matrix.multiplyEntry(i, j, (1/matrix.getEntry(i, ind)));
	}
	
	public double[][] getMatrix() {	
		return matrix.getData();		
	}
	
}
















