package SistemaBiblioteca.src.components.livros;

import SistemaBiblioteca.src.components.usuarios.ObservadorReserva;

public interface ILivroObservavel {
    public void registraObservador(ObservadorReserva observador);
    public boolean removeObservador(ObservadorReserva observador);
    public void notificaObservadores();
}
