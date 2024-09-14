package SistemaBiblioteca.src.frontend.comandos;

public interface Comando {
    public Object executar(int ... params) throws InterruptedException;
}
