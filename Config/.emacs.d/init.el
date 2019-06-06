
;; Added by Package.el.  This must come before configurations of
;; installed packages.  Don't delete this line.  If you don't want it,
;; just comment it out by adding a semicolon to the start of the line.
;; You may delete these explanatory comments.
(package-initialize)

;;关闭工具栏
(tool-bar-mode -1)

;;关闭滑动条
(scroll-bar-mode -1)

;;关闭缩进
;(electric-indent-mode -1)

;;关闭启动tutorial画面
(setq inhibit-splash-screen t)

;;显示行数
(global-linum-mode t)

(defun open-my-init-file ()
  (interactive)
  (find-file "~/.emacs.d/init.el"))

(global-set-key (kbd "<f2>") 'open-my-init-file)

;;开启全局company补全
(global-company-mode t)

;;修改光标为bar
(setq-default cursor-type 'bar)

;;禁止生成备份文件
(setq make-backup-files nil)

;;最近的文件在图形菜单中进行显示
(require 'recentf)
(recentf-mode 1)
(setq recentf-max-menu-item 10)


;(recentf-mode t)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages (quote (company))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
