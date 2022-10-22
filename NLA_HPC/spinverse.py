import numpy as np
from scipy import sparse
from scipy.sparse import linalg
#
def sai( A ):
    # obtain the inverse-M by minimizing the F-norm of (AM-I).
    N = A.shape[0]
    #switch to csc storage.
    A = A.tocsc()
    #
    M = sparse.csc_matrix( (N,N), dtype=A.dtype )
    I = sparse.eye(N).tocsc()
    for i in range(N):
        Nonzero_count = A[ :, i ].count_nonzero()
        print( Nonzero_count )
        Nonzero_vector = A[ :, i ].nonzero()
        Nonzero_row = np.array(Nonzero_vector[0]).reshape( Nonzero_count )
        locA = A[ :, Nonzero_row ]
        locATA = locA.T @ locA
        rhs = locA.T @ I[:, i]
        x = linalg.spsolve( locATA, rhs )
        M[Nonzero_row,i] = x
    return M
#
print( '=============test case 1: diagonal matrix============' )
N = 5
A = sparse.eye( N )
M = sai(A)
print( M )
#
print( '=============test case 2: random dense matrix============' )
N = 5
A = np.random.rand( N,N )
#M = sai(A)
M0 = np.linalg.inv(A)
#print(M)
print(M0)
A = sparse.csc_matrix( A )
M = sai(A)
print(M.todense())
print( M-M0 )
if ( (np.abs(M.todense()-M0)<=1.0e-8).all() ):
    print( "Solution is correct!" )
else:
    print("wrong sai!")
