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
        private const string _firstLineTag = "/*!";
        private const string _normalLineTag = "";
        private const string _lastLineTag = "*/";
        private const string _commandPrefix = "@";

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public JavaDocComment()
        {
            // no-op
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

            rv.Add(_firstLineTag);

            return rv;
        }

        /// <summary>
        /// 共通コメントフッター生成処理
        /// </summary>
        /// <param name="codeElem">解析対象の要素</param>
        /// <param name="buffer">フッター追加対象配列</param>
        private void AppendCommentFooter(VCCodeElement codeElem, ArrayList buffer)
        {
            buffer.Add(_lastLineTag);
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

            rv.Add(_firstLineTag);
            rv.Add(_normalLineTag + "ここに" + doc.Name + "の概要を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "file\t" + doc.Name);
            rv.Add(_normalLineTag + _commandPrefix + "date\t" + now.ToString("yyyy/MM/dd"));
            rv.Add(_lastLineTag);

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
            rv.Add(_normalLineTag + _commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
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
            rv.Add(_normalLineTag + _commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
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
            //        rv.Add(_normalLineTag + _commandPrefix + "param   " + curParam.Name
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
            rv.Add(_normalLineTag + _commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
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
            rv.Add(_normalLineTag + _commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
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

            rv.Add(_firstLineTag + " ここに" + codeElem.Name + "の概要を記載.");
            // DEL 20130502 20:35:53 sunada@ipl Start -->
            //if (codeElem.Parameters.Count > 0)
            //{
            //    foreach (VCCodeParameter curParam in codeElem.Parameters)
            //    {

            //        rv.Add(_normalLineTag + _commandPrefix + "param   " + curParam.Name
            //            + " パラメータ" + curParam.Name + "の説明を記載.");
            //    }
            //}
            //rv.Add(_normalLineTag + _commandPrefix + "see     ");
            // DEL 20130502 20:35:53 sunada@ipl  End  <--
            // Create /returns section
            if ((codeElem.TypeString.Length > 0) &
                (codeElem.TypeString.ToLower() != "void"))
            {
                rv.Add(_normalLineTag + _commandPrefix + "return\t" + "ここに戻り値の説明を記載.");
                rv.Add(_normalLineTag + _commandPrefix + "retval\t" + "ここに戻り値の説明を記載.");
                rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
            }

            // DEL 20130502 20:41:22 sunada@ipl Start -->
            //rv.Add(_normalLineTag + _commandPrefix + "throws <exception class> この例外を投げるための基準の説明を記載.");
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
            rv.Add(_normalLineTag + _commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
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
            rv.Add(_normalLineTag + _commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
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
            rv.Add(_normalLineTag + _commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
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
            rv.Add(_normalLineTag + _commandPrefix + "brief\t" + "ここに" + codeElem.Name + "の要約を記載.");
            rv.Add(_normalLineTag + _commandPrefix + "note\t" + "ここに" + codeElem.Name + "の詳細を記載.");
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
                    rv.Add(_normalLineTag + _commandPrefix + "param\t" + typeStr + " パラメータ" + typeStr + "の説明を記載.");
                }
            }
            AppendCommentFooter((VCCodeElement)codeElem, rv);

            return (string[])rv.ToArray(typeof(string));
        }
        #endregion
    }
}