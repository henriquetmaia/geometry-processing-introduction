#include "euler_characteristic.h"
#include "edges.h"

int euler_characteristic(const Eigen::MatrixXi &F)
{
	int Chi;
	// Nah man, you add it

	Eigen::VectorXi verts(F.rows() * 3);
	verts.setZero();

	for( int f = 0; f < F.rows(); ++f ){
		verts[F(f,0)] = 1;
		verts[F(f,1)] = 1;
		verts[F(f,2)] = 1;
	}

	int V = verts.sum();

	Chi = V - edges(F).rows() + F.rows();

	return Chi;
}
