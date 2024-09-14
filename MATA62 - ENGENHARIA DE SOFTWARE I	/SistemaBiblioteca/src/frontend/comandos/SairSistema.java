package SistemaBiblioteca.src.frontend.comandos;

public class SairSistema implements Comando {

    @Override
    public Object executar(int ... params) throws InterruptedException {
        throw new InterruptedException("Você saiu do sistema com sucesso.");
    }
}

