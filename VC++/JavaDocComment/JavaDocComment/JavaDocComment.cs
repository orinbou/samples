using System;
using System.Collections;
using DoxyComment;
using EnvDTE;
using System.ComponentModel;
using Microsoft.VisualStudio.VCCodeModel;

namespace JavaDocComment
{
    /// <summary>
    /// Doxygenコメント雛形生成処理クラス
    /// </summary>
    [CommentProviderFriendlyName("JavaDocComment")]
    public class JavaDocComment : DoxyComment.ICommentProvider
    {
        [CommentProviderProperty]
        private string firstLineTag = "/*!";
        [CommentProviderProperty]
        private string normalLineTag = "";
        [CommentProviderProperty]
        private string lastLineTag = " */";
        [CommentProviderProperty]
        private string commandPrefix = "@";
        [CommentProviderProperty]
        private string author = "";

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public JavaDocComment()
        {
            // no-op
        }

        [Category("コメントブロック概観"),
        Description("コメントブロックの先頭行の接頭辞です.")]
        public string FirstLineTag
        {
            get
            {
                return firstLineTag;
            }
            set
            {
                firstLineTag = value;
            }
        }

        [Category("コメントブロック概観"),
       Description("コメントブロックの行の接頭辞です.")]
        public string NormalLineTag
        {
            get
            {
                return normalLineTag;
            }
            set
            {
                normalLineTag = value;
            }
        }

        [Category("コメントブロック概観"),
       Description("コメントブロックの最終行の接頭辞です.")]
        public string LastLineTag
        {
            get
            {
                return lastLineTag;
            }
            set
            {
                lastLineTag = value;
            }
        }
        [Category("コマンド接頭辞"),
        Description("コマンドの接頭辞です。\\や@を指定します.")]
        public string CommandPrefix
        {
            get
            {
                return commandPrefix;
            }
            set
            {
                commandPrefix = value;
            }
        }
        [Category("制作者"),
        Description("制作者を指定します.")]
        public string Author
        {
            get
            {
                return author;
            }
            set
            {
                author = value;
            }
        }
        
        #region ICommentProvider implementation

        /// <summary>
        /// 共通コメントヘッダー生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        private ArrayList CreateCommentHeader(VCCodeElement codeElem)
        {
            ArrayList rv = new ArrayList();

            rv.Add(this.firstLineTag);

            return rv;
        }

        /// <summary>
        /// 共通コメントフッター生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <param name="buffer">フッター追加対象配列</param>
        private void AppendCommentFooter(VCCodeElement codeElem, ArrayList buffer)
        {
            buffer.Add(this.lastLineTag);
        }

        /// <summary>
        /// ファイルコメント生成処理
        /// </summary>
        /// <param name="doc">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateFileComment(Document doc)
        {
            ArrayList rv = new ArrayList();
            DateTime now = DateTime.Now;

            rv.Add(this.firstLineTag);
            rv.Add(this.normalLineTag + "ここに" + doc.Name + "の概要を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "file\t" + doc.Name);
            rv.Add(this.normalLineTag + this.commandPrefix + "date\t" + now.ToString("yyyy/MM/dd"));
            rv.Add(this.lastLineTag);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// typedefコメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateTypeDefComment(VCCodeTypedef codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            rv.Add(this.normalLineTag + this.commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// 共用体コメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateUnionComment(VCCodeUnion codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            rv.Add(this.normalLineTag + this.commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// マクロコメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateMacroComment(VCCodeMacro codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            //if ((codeElem.Parameters.Count > 0))
            //{
            //    foreach (VCCodeParameter curParam in codeElem.Parameters)
            //    {
            //        rv.Add(this.normalLineTag + this.commandPrefix + "param   " + curParam.Name
            //            + " パラメータ" + curParam.Name + "の説明を記載.");
            //    }
            //}
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// 構造体コメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateStructComment(VCCodeStruct codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            rv.Add(this.normalLineTag + this.commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// ネームスペースコメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateNamespaceComment(VCCodeNamespace codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            rv.Add(this.normalLineTag + this.commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// 関数コメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateFunctionComment(VCCodeFunction codeElem)
        {
            ArrayList rv = new ArrayList();

            rv.Add(this.firstLineTag + " ここに" + codeElem.Name + "の概要を記載.");
            // DEL 20130502 20:35:53 sunada@ipl Start -->
            //if (codeElem.Parameters.Count > 0)
            //{
            //    foreach (VCCodeParameter curParam in codeElem.Parameters)
            //    {

            //        rv.Add(this.normalLineTag + this.commandPrefix + "param   " + curParam.Name
            //            + " パラメータ" + curParam.Name + "の説明を記載.");
            //    }
            //}
            //rv.Add(this.normalLineTag + this.commandPrefix + "see     ");
            // DEL 20130502 20:35:53 sunada@ipl  End  <--
            // Create /returns section
            if ((codeElem.TypeString.Length > 0) &
                (codeElem.TypeString.ToLower() != "void"))
            {
                rv.Add(this.normalLineTag + this.commandPrefix + "return\t" + "ここに戻り値の説明を記載.");
                rv.Add(this.normalLineTag + this.commandPrefix + "retval\t" + "ここに戻り値の説明を記載.");
                rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            }

            // DEL 20130502 20:41:22 sunada@ipl Start -->
            //rv.Add(this.normalLineTag + this.commandPrefix + "throws <exception class> この例外を投げるための基準の説明を記載.");
            // DEL 20130502 20:41:22 sunada@ipl  End  <--

            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// Enum値コメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateEnumValueComment(VCCodeVariable codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            rv.Add(this.normalLineTag + this.commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// Enumコメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateEnumComment(VCCodeEnum codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            rv.Add(this.normalLineTag + this.commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// 値コメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateVariableComment(VCCodeVariable codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            rv.Add(this.normalLineTag + this.commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }

        /// <summary>
        /// クラスコメント生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <returns>生成したコメント文字列</returns>
        public string[] CreateClassComment(VCCodeClass codeElem)
        {
            ArrayList rv;

            rv = CreateCommentHeader((VCCodeElement)codeElem);
            rv.Add(this.normalLineTag + this.commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(this.normalLineTag + this.commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            if ((codeElem.IsTemplate))
            {
                foreach (VCCodeParameter curTemplateParam in codeElem.Templatizations)
                {
                    string typeStr;
                    if ((curTemplateParam.Name.Length != 0))
                    {
                        typeStr = curTemplateParam.Name;
                    }
                    else
                    {
                        int typeIdx;

                        typeIdx = curTemplateParam.TypeString.LastIndexOf(" ");
                        typeStr = curTemplateParam.TypeString.Substring(typeIdx + 1);
                    }
                    rv.Add(this.normalLineTag + this.commandPrefix + "param\t" + typeStr + " パラメータ" + typeStr + "の説明を記載.");
                }
            }
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }
        #endregion
    }
}