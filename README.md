# Projeto-Bobinadeira
Projeto Bobinadeira Automática. Made by Matheus De Freitas.

Projeto feito para a situação de aprendizagem final do curso de Elétrica Industrial do Senai.

O projeto consiste em uma bobinadeira automática de transformadores. A parte eletrônica é feita usando uma placa Arduino UNO, que controla dois motores DG01D-A130 controlados por Drivers de ponte H BTS7960. O fio de cobre sai de um rolo, passa pelo primeiro motor, que controla a direção do fio, e passa para o carretel do transformador, no qual é girado pelo segundo motor. Os dois motores funcionam sincronizados, de forma que o fio de cobre é enrolado no carretel de froma constante e justa.
O sistema é acionado por um fim de curso acoplado a um pedal, que aciona os dois motores. Caso o operador da máquina tire o pé do pedal, desacionando o fim de curso, o sistema irá parar de funcionar.
O primeiro motor, no qual controla a direção do fio de cobre, gira uma plataforma de ferro por onde o fio passa. Abaixo dessa plataforma, ficam posicionados dois sensores (INDUTIVOS OU CAPACITIVOS), que delimitam até onde o fio de cobre pode se mover. Os sensores possuem um intervalo de espaço igual à medida do comprimento do carretel do transformador. O fio de cobre que passa pela plataforma de ferro só irá se mover dentro desse intervalo de espaço entre os sensores.
O motor irá começar girando no sentido horário, até chegar no sensor, o qual irá mandá-lo girar no sentido anti-horário. O processo deve se repetir até que o número de voltas feitas no carretel seja completada.
