#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int thresh = 100;

int main(int, char** argv)
{

    Mat src = imread("11.jpg");

    //Verifica��o se a imagem est� vazia
    if (!src.data)
        return -1;

    // Exibe a imagem original
    imshow("Original", src);

    //Converte a imagem original para escala de cinza
    Mat destino = src;
    cvtColor(src, destino, CV_BGR2GRAY);
    // imshow("Escala de cinza", destino);

    //Transformada da dist�ncia para resolver a oclus�o de alguns gr�os


    //Realiza o corte do fundo, para destacar apenas objetos relevantes
    threshold(destino, destino, 120, 250, 0);
    // threshold(destino, destino, 128, 255, CV_THRESH_OTSU | CV_THRESH_OTSU);
    imshow("Ap�s o threshold bin�rio", destino);

    // MORPH_RECT
    // MORPH_CROSS
    // MORPH_ELLIPSE
    Mat kernel1 = getStructuringElement( MORPH_ELLIPSE, Size(13, 13), Point(8, 8) );

    dilate(destino, destino, kernel1);

    imshow("Ap�s dilata��o", destino);

    Mat dist;
    Mat copia = destino, resultado;

    distanceTransform(destino, dist, CV_DIST_L2, 3);
    normalize(dist, dist, 0, 1., NORM_MINMAX);
    imshow("Transformada da dist�ncia", dist);



    //Novo threshold feito sobre a transformada para separar os gr�os
    threshold(dist, destino, .01, 1., CV_THRESH_BINARY);
    imshow("Novo threshold ap�s a transformada de dist�ncia", destino);

    dilate(destino, destino, kernel1);

    erode(destino, destino, kernel1);
    erode(destino, destino, kernel1);

    erode(destino, destino, kernel1);

    dilate(destino, destino, kernel1);
//resultado = copia - dist;

//Para fazer a detec��o de bordas � necess�rio converter a imagem para CV_8U
    Mat dist_8u;

    Mat teste;

    //Os contornos ser�o armazenados em vetor de pontos
    vector<vector<Point> > contours;

    //Encontra os contornos em uma imagem bin�ria
    //CV_RETR_EXTERNAL recupera os contornos externos
    //CV_CHAIN_APPROX_SIMPLE comprime os segmentos horizontais, verticais e diagonais,
    //deixando apenas os seus pontos finais - � um m�todo de aproxima��o

    threshold(destino, destino, .01, 1., CV_THRESH_BINARY);
    //destino.convertTo(destino, CV_8U);

      Canny(destino, teste, thresh, thresh*2, 3, false);

   cout << "teste" << endl;


    findContours(teste, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
/*

    //Retorna uma matriz zeros do tamanho e do tipo especificado (CV_32SC1)
    Mat markers = Mat::zeros(dist.size(), CV_32SC1);

    //Desenha os marcadores no primeiro plano
    for (size_t i = 0; i < contours.size(); i++)
        drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);

    //Desenha os marcadores de fundo
    circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);

    //O watershed � aplicado para englobar o m�ximo de pixels poss�veis dos vales at� os topos
    //Retorna o tamanho mais fiel dos gr�os que foi diminu�do na transformada de dist�ncia
    watershed(src, markers);

    //Retorna outra matriz zeros do tamanho e do tipo especificado (CV_8UC1)
    Mat mark = Mat::zeros(markers.size(), CV_8UC1);

    //Converte a imagem para CV_8UC1
    markers.convertTo(mark, CV_8UC1);

    //Inverte os bits do array mark
    bitwise_not(mark, mark);

    //Um vetor para armazenar as cores randomicamente � criado
    //Logo em seguida o vetor de cores � iniciado com as cores
    vector<Vec3b> cores;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 255);
        int g = theRNG().uniform(0, 255);
        int r = theRNG().uniform(0, 255);
        cores.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    //Cria a imagem de resultado
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);

    //Preenche (rotula) os objetos marcados com as cores alet�rias existentes no vetor 'colors'
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
                dst.at<Vec3b>(i,j) = cores[index-1];
            else
                dst.at<Vec3b>(i,j) = Vec3b(0,0,0);
        }
    }

    //Exibe a imagem final
    imshow("Resultado final", dst);
*/

    imshow("Final", destino);


    //Para fazer a detec��o de bordas � necess�rio converter a imagem para CV_8U
    //Mat dist_8u;
    //dist.convertTo(dist_8u, CV_8U);

    //Os contornos ser�o armazenados em vetor de pontos
    // vector<vector<Point> > contours;

    //Encontra os contornos em uma imagem bin�ria
    //CV_RETR_EXTERNAL recupera os contornos externos
    //CV_CHAIN_APPROX_SIMPLE comprime os segmentos horizontais, verticais e diagonais,
    //deixando apenas os seus pontos finais - � um m�todo de aproxima��o
    //  findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    //Retorna uma matriz zeros do tamanho e do tipo especificado (CV_32SC1)
    //  Mat markers = Mat::zeros(dist.size(), CV_32SC1);

    //Desenha os marcadores no primeiro plano
    //for (size_t i = 0; i < contours.size(); i++)
    //    drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);

    //Desenha os marcadores de fundo
//   circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);

    //Exibe os marcadores que j� foram desenhados
//   imshow("Marcadores", markers*10000);

    //O watershed � aplicado para englobar o m�ximo de pixels poss�veis dos vales at� os topos
    //Retorna o tamanho mais fiel dos gr�os que foi diminu�do na transformada de dist�ncia
    //  watershed(src, markers);

    //Retorna outra matriz zeros do tamanho e do tipo especificado (CV_8UC1)
    // Mat mark = Mat::zeros(markers.size(), CV_8UC1);

    //Converte a imagem para CV_8UC1
    // markers.convertTo(mark, CV_8UC1);

    //Inverte os bits do array mark
    //bitwise_not(mark, mark);

    //Um vetor para armazenar as cores randomicamente � criado
    //Logo em seguida o vetor de cores � iniciado com as cores
    //  vector<Vec3b> cores;
    //  for (size_t i = 0; i < contours.size(); i++)
    //  {
    //      int b = theRNG().uniform(0, 255);
    //      int g = theRNG().uniform(0, 255);
    //      int r = theRNG().uniform(0, 255);
    //      cores.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    //  }

    //Cria a imagem de resultado
    //  Mat dst = Mat::zeros(markers.size(), CV_8UC3);

    //Preenche (rotula) os objetos marcados com as cores alet�rias existentes no vetor 'colors'
//   for (int i = 0; i < markers.rows; i++)
//   {
    //     for (int j = 0; j < markers.cols; j++)
//{
    //      int index = markers.at<int>(i,j);
    //      if (index > 0 && index <= static_cast<int>(contours.size()))
    //         dst.at<Vec3b>(i,j) = cores[index-1];
    //     else
    //       dst.at<Vec3b>(i,j) = Vec3b(0,0,0);
    //}
    //}

    //Exibe a imagem final
    // imshow("Resultado final", dst);

    //Exibe o n�mero de elementos existem na imagem
    //  cout << "Quantidade de graos na imagem: " << contours.size() << endl;


    waitKey(0);
    return 0;
}
