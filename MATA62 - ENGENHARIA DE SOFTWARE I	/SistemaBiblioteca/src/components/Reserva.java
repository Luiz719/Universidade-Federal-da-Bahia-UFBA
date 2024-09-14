package SistemaBiblioteca.src.components;

import java.time.LocalDateTime;

import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.Usuario;

public class Reserva {
    private Livro livro;
    private int coDUsuario;
    private LocalDateTime dataReserva;

    public Reserva(Livro livro, Usuario solicitante) {
        this.livro = livro;
        this.coDUsuario = solicitante.getID();
        this.dataReserva = LocalDateTime.now();
    }

    public int getCodLivro(){
        return livro.getId();
    }

    public int getCodUsuario(){
        return coDUsuario;
    }

    public LocalDateTime getDataReserva(){
        return dataReserva;
    }

}
