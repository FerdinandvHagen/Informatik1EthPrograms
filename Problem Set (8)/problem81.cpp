#include <iostream>

void input_vector(float res[3])
{
    std::cout << "Please Enter three floats which will form the vector" << std::endl;
    for(int i = 0; i<3; i++)
    {
        std::cin >> res[i];
    }
}

float scalar_product(const float v1[3], const float v2[3])
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void input_matrix(float res[3][3])
{
    std::cout << "Please enter Numbers to form an 3x3 Matrix" << std::endl;

    for(int i = 0; i<3; i++)
    {
        std::cout << "Row number: " << i << std::endl;
        input_vector(res[i]);
    }
}

void output_matrix(const float res[3][3])
{
    std::cout << "The given Matrix is: " << std::endl;

    for(int i = 0; i<3; i++)
    {
        for(int l = 0; l<3; l++)
        {
            std::cout << res[i][l] << " ";
        }
        std::cout << std::endl;
    }
}

void matrix_multiplication(const float a[3][3], const float b[3][3], float res[3][3]){
    for(int i = 0; i<3; i++){
        for(int l = 0; l<3; l++){
            float sum = 0;
            for(int s = 0; s<3; s++){
                sum += a[i][s] * b[s][l];
            }
            res[i][l] = sum;
        }
    }
}

int main()
{
    float v1[3], v2[3];
    input_vector(v1);
    input_vector(v2);
    std::cout << "Scalar Product: " << scalar_product(v1, v2) << std::endl << std::endl;

    float m1[3][3], m2[3][3], m3[3][3];
    input_matrix(m1);
    input_matrix(m2);

    matrix_multiplication(m1, m2, m3);

    output_matrix(m3);

    return 0;
}





