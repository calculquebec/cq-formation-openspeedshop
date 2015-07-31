#PBS -l nodes=1:ppn=8
#PBS -A six-213-ad
#PBS -l walltime=24:00:00

cd /clumeq/formation/Debogage_Profilage/MatMul
module load compilers/gcc blas-libs/mkl tools/openspeedshop misc-libs/papi

for e in matmul0_perf.out matmul1_perf.out matmul2_perf.out matmulmkl_perf.out; do
	./script.sh $e > ${e}_profile_multithread
done
export OMP_NUM_THREADS=1
for e in matmul0_perf.out matmul1_perf.out matmul2_perf.out matmulmkl_perf.out; do
	./script.sh $e > ${e}_profile_singlethread
done

